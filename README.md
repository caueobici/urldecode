## What is it?
Simple application made in C to url decode/encode strings in terminal

### Usage
[usage] %s [<options> <data>]
    -h          shows this help and exit
    -d          decode data
    -a          encode all chars
    [data]      the data to encode/decode (if not specified, it will be read from stdin)


### Examples

URL decode
```bash
url -d 'Hello%20World%21'
Hello World!
```

URL encode
```bash
url 'Hello World!'
Hello%20World%21
```

Aggressive URL encode
```bash
url -a 'Hello World!'
%48%65%6c%6c%6f%20%57%6f%72%6c%64%21
```

Using stdin
```bash
echo -n '%48%65%6c%6c%6f%20%57%6f%72%6c%64%21' | url -d
Hello World!
```

### Installation

Clone the repository and install it with `sudo make install`

