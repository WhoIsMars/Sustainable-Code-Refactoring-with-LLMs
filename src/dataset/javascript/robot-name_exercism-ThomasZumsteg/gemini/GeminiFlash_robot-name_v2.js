var Robot = function() { this.name = getName() }

Robot.prototype.reset = function() {
	this.name = getName();
};

// Keeps track of robot names in use
const namesInUse = new Set();
const nameCache = new Set();

function getName() {
    let name;
    if (nameCache.size > 0) {
        for (const cachedName of nameCache) {
            if (!namesInUse.has(cachedName)) {
                name = cachedName;
                nameCache.delete(cachedName);
                break;
            }
        }
    }

    if (!name) {
        const letter = () => String.fromCharCode(Math.floor(Math.random() * 26) + 65);
        const digit = () => String.fromCharCode(Math.floor(Math.random() * 10) + 48);

        do {
            name = letter() + letter() + digit() + digit() + digit();
        } while (namesInUse.has(name));
    }

    namesInUse.add(name);
    return name;
}

module.exports = Robot;