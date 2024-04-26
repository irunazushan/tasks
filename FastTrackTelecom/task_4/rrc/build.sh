rm -r src/*
rm -r build/*
mkdir src
mkdir build
asn1c rrc.asn1 -D src -pdu=auto -no-gen-OER -fcompound-names -no-gen-example -fno-include-deps
gcc -g -Isrc -I. -o build/rrc_coder main.c rrc_coder.c src/*.c -lsctp -DPDU=auto -DASN_DISABLE_OER_SUPPORT
./build/server
gcc -g -Isrc -I. -o build/server server/server.c src/*.c -lsctp -DPDU=auto -DASN_DISABLE_OER_SUPPORT
./build/rrc_coder
