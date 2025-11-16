FROM gcc:latest

WORKDIR /app

ENV DEBIAN_FRONTEND=noninteractive

# Installa le dipendenze base
RUN apt-get update && apt-get install -y \
    make \
    g++ \
    libboost-test-dev \
    libboost-date-time-dev \
    libboost-regex-dev \
    libboost-system-dev \
    libboost-filesystem-dev \
    pkg-config \
    wget \
    curl \
    valgrind \
    time \
    git \
    python3 \
    cmake \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Installa Catch2 (versione 2.x per compatibility con exercism tests)
# Download the single-header version which is what Exercism expects
RUN mkdir -p /usr/local/include/catch2 && \
    wget -O /usr/local/include/catch2/catch.hpp https://raw.githubusercontent.com/catchorg/Catch2/v2.13.10/single_include/catch2/catch.hpp && \
    echo "Downloaded Catch2 single-header to /usr/local/include/catch2/catch.hpp"

# Verifica l'installazione (utile per debugging)
RUN ls -l /usr/include/boost/test/unit_test.hpp || echo "Boost.Test header not found"
RUN ls -l /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so || echo "Boost.Test library not found"
RUN ls -l /usr/local/include/catch2/catch_all.hpp || echo "Catch2 header not found"

# Aggiorna ldconfig per assicurarsi che le librerie siano trovate
RUN ldconfig

# Copia i file di configurazione
COPY . .
COPY time_wrapper.py /usr/local/bin/time_wrapper.py
COPY Makefile.universal /usr/local/share/Makefile.universal

RUN chmod +x /usr/local/bin/time_wrapper.py

#ENTRYPOINT ["bash", "run.sh"]