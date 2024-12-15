# PaybackOS
A simple 64 bit operating system

## Building
run this command (linux)
```bash
docker build buildenv -t paybackos-buildenv
```
```bash
docker run --rm -it -v "$(pwd)":/root/env paybackos-buildenv
```
This will put you into a shell. Now run this command inside the docker shell
```bash
make build-x86_64
```