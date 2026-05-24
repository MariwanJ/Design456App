#!/bin/bash

for file in *.off; do
    name="${file%.off}"
    xxd -i "$file" > "${name}.h"
    echo "converted $file -> ${name}.h"
done

echo "done!"
