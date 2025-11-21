#!/bin/bash
#set -e
set -eo pipefail

# Usa un percorso assoluto per il file di log
LOG_FILE="/app/output.log"
# Pulisci il log all'inizio
> "$LOG_FILE"

echo "🧹 Pulizia file precedenti..." | tee -a "$LOG_FILE"
echo "[INFO] Starting run.sh at $(date)" >> "$LOG_FILE"


echo "[INFO] Checking build system..." >> "$LOG_FILE"

if [ -f "CMakeLists.txt" ]; then
    echo "📦 Detected CMake build system" | tee -a "$LOG_FILE"
    echo "[INFO] Using CMake." >> "$LOG_FILE"
    BUILD_SYSTEM="cmake"
    rm -rf build || true
elif [ -f "Makefile" ] || [ -f "makefile" ]; then
    echo "🔧 Detected Make build system" | tee -a "$LOG_FILE"
    echo "[INFO] Using Makefile." >> "$LOG_FILE"
    BUILD_SYSTEM="make"
    make clean >> "$LOG_FILE" 2>&1 || true
else
    echo "⚠️  No build system detected, will try CMake as default" | tee -a "$LOG_FILE"
    echo "[WARN] No build system detected — defaulting to CMake." >> "$LOG_FILE"
    BUILD_SYSTEM="cmake"
fi

echo "🔧 Compilazione..." | tee -a "$LOG_FILE"
echo "[INFO] Starting compilation pipeline..." >> "$LOG_FILE"

if [ "$BUILD_SYSTEM" = "cmake" ]; then
    CMAKE_SUCCESS=0
    CMAKE_FLAGS=""

    echo "[INFO] Checking for Exercism CMake flags..." >> "$LOG_FILE"
    if grep -q "EXERCISM_TEST_SUITE" CMakeLists.txt 2>/dev/null; then
        CMAKE_FLAGS="-DEXERCISM_TEST_SUITE=1 -DEXERCISM_RUN_ALL_TESTS=1"
        echo "🎯 Detected Exercism CMakeLists, using flags: $CMAKE_FLAGS" | tee -a "$LOG_FILE"
        echo "[INFO] Exercism flags enabled." >> "$LOG_FILE"

        if [ -n "$EXERCISM_EXERCISE_NAME" ]; then
            echo "[INFO] EXERCISM_EXERCISE_NAME=$EXERCISM_EXERCISE_NAME" >> "$LOG_FILE"

            WORK_DIR="/app/$EXERCISM_EXERCISE_NAME"
            mkdir -p "$WORK_DIR"
            echo "🔧 Creating directory: $WORK_DIR" | tee -a "$LOG_FILE"

            echo "[INFO] Copying project files to $WORK_DIR" >> "$LOG_FILE"
            for item in *; do
                if [ "$item" != "build" ] && [ "$item" != "$EXERCISM_EXERCISE_NAME" ]; then
                    cp -r "$item" "$WORK_DIR/"
                fi
            done

            echo "📁 Switching to directory: $WORK_DIR" | tee -a "$LOG_FILE"
            cd "$WORK_DIR"
            echo "[INFO] Entered directory $(pwd)" >> "$LOG_FILE"

            if [ -f "CMakeLists.txt" ] && [ -d "src" ] && [ -d "test" ]; then
                echo "[INFO] Patching CMakeLists.txt include paths..." >> "$LOG_FILE"
                sed -i 's|\${file}\.c|src/\${file}.c|g; s|\${file}\.h|src/\${file}.h|g; s|\${file}_test\.c|test/\${file}_test.c|g' CMakeLists.txt

                if ! grep -q "include_directories(src)" CMakeLists.txt 2>/dev/null; then
                    sed -i '/^project(/a include_directories(src)\ninclude_directories(test)\ninclude_directories(${CMAKE_SOURCE_DIR})' CMakeLists.txt
                    echo "✓ Added include_directories for src/, test/, and source root" | tee -a "$LOG_FILE"
                    echo "[INFO] include_directories injected." >> "$LOG_FILE"
                fi
            fi
        else
            echo "⚠️  EXERCISM_EXERCISE_NAME not set, using current directory" | tee -a "$LOG_FILE"
        fi
    fi

    mkdir -p build
    cd build
    echo "[INFO] Running cmake configuration..." >> "$LOG_FILE"

    export CFLAGS="-O0 -g0"

    if ! cmake $CMAKE_FLAGS .. >> "$LOG_FILE" 2>&1; then
        echo "[ERROR] CMake configuration failed." >> "$LOG_FILE"
        echo "❌ CMake configuration failed" | tee -a "$LOG_FILE"
        cmake $CMAKE_FLAGS ..
        cd ..
        CMAKE_SUCCESS=1
    fi

    echo "[INFO] Running build step..." >> "$LOG_FILE"
    if [ $CMAKE_SUCCESS -eq 0 ] && ! cmake --build . -j1 >> "$LOG_FILE" 2>&1; then
        echo "[ERROR] CMake build failed." >> "$LOG_FILE"
        echo "❌ CMake build failed" | tee -a "$LOG_FILE"
        cmake --build . -j1
        cd ..
        CMAKE_SUCCESS=1
    fi

    if [ $CMAKE_SUCCESS -eq 1 ]; then
        echo "[WARN] Entering fallback build mode..." >> "$LOG_FILE"
        echo "⚠️  CMake failed, attempting fallback to universal Makefile..." | tee -a "$LOG_FILE"

        if [ -n "$EXERCISM_EXERCISE_NAME" ] && [ -d "/app/$EXERCISM_EXERCISE_NAME" ]; then
            cd "/app/$EXERCISM_EXERCISE_NAME"
        else
            cd /app
        fi

        if [ -f "Makefile.fallback" ]; then
            echo "[INFO] Using fallback Makefile..." >> "$LOG_FILE"
            cp Makefile.fallback Makefile

            if make >> "$LOG_FILE" 2>&1; then
                echo "✅ Fallback to universal Makefile succeeded" | tee -a "$LOG_FILE"
                echo "[INFO] Fallback build succeeded." >> "$LOG_FILE"
                CMAKE_SUCCESS=0
            else
                echo "[ERROR] Fallback Makefile failed." >> "$LOG_FILE"
                echo "❌ Universal Makefile fallback also failed" | tee -a "$LOG_FILE"
                exit 1
            fi
        else
            echo "[ERROR] Missing fallback Makefile" >> "$LOG_FILE"
            echo "❌ No fallback Makefile available after CMake failure" | tee -a "$LOG_FILE"
            exit 1
        fi
    else
        echo "[INFO] Searching for test executable..." >> "$LOG_FILE"
        TEST_EXEC=$(find . -maxdepth 2 -type f -executable -name "*test*" | head -1)
        if [ -z "$TEST_EXEC" ]; then
            TEST_EXEC=$(find . -maxdepth 2 -type f -executable ! -name "*.so" ! -name "*.dylib" | head -1)
        fi

        if [ -z "$TEST_EXEC" ]; then
            echo "[ERROR] No executable found after build." >> "$LOG_FILE"
            echo "❌ No test executable found after CMake build" | tee -a "$LOG_FILE"
            ls -la >> "$LOG_FILE" 2>&1
            cd ..
            exit 1
        fi

        echo "✅ Found test executable: $TEST_EXEC" | tee -a "$LOG_FILE"
        echo "[INFO] TEST_EXEC=$TEST_EXEC" >> "$LOG_FILE"
        cp "$TEST_EXEC" ../tests.out
        cd ..
    fi

    if [ -n "$EXERCISM_EXERCISE_NAME" ]; then
        echo "[INFO] Copying executable back to /app..." >> "$LOG_FILE"
        cp tests.out /app/tests.out
        cd /app
    fi

elif [ "$BUILD_SYSTEM" = "make" ]; then
    echo "[INFO] Using Makefile build..." >> "$LOG_FILE"

    if [ -f "Makefile" ]; then
        echo "🔨 Attempting build with existing Makefile..." | tee -a "$LOG_FILE"

        if ! make >> "$LOG_FILE" 2>&1; then
            echo "[WARN] Makefile failed — using fallback" >> "$LOG_FILE"
            echo "⚠️  Original Makefile failed, trying universal Makefile..." | tee -a "$LOG_FILE"

            mv Makefile Makefile.original

            if [ -f "Makefile.fallback" ]; then
                cp Makefile.fallback Makefile
                if ! make >> "$LOG_FILE" 2>&1; then
                    echo "[ERROR] Fallback Makefile failed" >> "$LOG_FILE"
                    echo "❌ Universal Makefile also failed" | tee -a "$LOG_FILE"
                    exit 1
                fi
                echo "✅ Universal Makefile succeeded" | tee -a "$LOG_FILE"
                echo "[INFO] Fallback Make build succeeded." >> "$LOG_FILE"
            else
                echo "[ERROR] Missing fallback Makefile" >> "$LOG_FILE"
                echo "❌ No fallback Makefile available" | tee -a "$LOG_FILE"
                exit 1
            fi
        fi
    else
        echo "📝 No Makefile found, using universal Makefile..." | tee -a "$LOG_FILE"
        echo "[INFO] No Makefile present — using fallback" >> "$LOG_FILE"

        if [ -f "Makefile.fallback" ]; then
            cp Makefile.fallback Makefile
            if ! make >> "$LOG_FILE" 2>&1; then
                echo "[ERROR] Universal Makefile failed." >> "$LOG_FILE"
                echo "❌ Universal Makefile failed" | tee -a "$LOG_FILE"
                exit 1
            fi
        else
            echo "[ERROR] No fallback Makefile found" >> "$LOG_FILE"
            echo "❌ No Makefile.fallback available" | tee -a "$LOG_FILE"
            exit 1
        fi
    fi
fi

if [ ! -f ./tests.out ]; then
    echo "[ERROR] tests.out missing — build invalid." >> "$LOG_FILE"
    echo "❌ Compilazione fallita: ./tests.out non trovato in /app" | tee -a "$LOG_FILE"
    ls -la >> "$LOG_FILE" 2>&1
    exit 1
fi

chmod +x ./tests.out
echo "[INFO] tests.out is executable." >> "$LOG_FILE"

echo "🧪 Esecuzione test con misurazione risorse..." | tee -a "$LOG_FILE"
echo "[INFO] Running tests with time_wrapper..." >> "$LOG_FILE"

if ! python3 "$(which time_wrapper.py)" ./tests.out >> "$LOG_FILE" 2>&1; then
    echo "[ERROR] time_wrapper failed" >> "$LOG_FILE"
    echo "❌ time_wrapper failed" | tee -a "$LOG_FILE"
fi

echo "[INFO] Running fallback time_wrapper path..." >> "$LOG_FILE"
if python3 /usr/local/bin/time_wrapper.py ./tests.out >> "$LOG_FILE" 2>&1; then
    echo "✅ Test eseguiti con successo" | tee -a "$LOG_FILE"
    echo "[INFO] Test execution completed successfully." >> "$LOG_FILE"
else
    EXIT_CODE=$?
    echo "[ERROR] Tests failed (exit $EXIT_CODE)" >> "$LOG_FILE"
    echo "❌ Test falliti (exit code: $EXIT_CODE) (echo run)" | tee -a "$LOG_FILE"
    exit $EXIT_CODE
fi

echo "🎉 Tutti i controlli completati" | tee -a "$LOG_FILE"
echo "[INFO] Finished run.sh at $(date)" >> "$LOG_FILE"
