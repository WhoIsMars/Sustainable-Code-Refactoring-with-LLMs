module.exports = {
    encode: function(text) {
        let result = '';
        let i = 0;
        const len = text.length;
        
        while (i < len) {
            const char = text[i];
            let count = 1;
            
            while (i + count < len && text[i + count] === char) {
                count++;
            }
            
            result += count > 1 ? count + char : char;
            i += count;
        }
        
        return result;
    },
    decode: function(text) {
        let result = '';
        let i = 0;
        const len = text.length;
        
        while (i < len) {
            let numStr = '';
            
            while (i < len && text[i] >= '0' && text[i] <= '9') {
                numStr += text[i];
                i++;
            }
            
            if (numStr && i < len) {
                const count = parseInt(numStr, 10);
                const char = text[i];
                
                for (let j = 0; j < count; j++) {
                    result += char;
                }
                i++;
            } else if (i < len) {
                result += text[i];
                i++;
            }
        }
        
        return result;
    }
};