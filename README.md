# This is for building firmware for the Nirvana NV14 Radio forked from the Flysky-OpenTX-Test-Branch project and maintained without any support

## WARNING: ...not an official branch ...do NOT use

## This is a playground for all new functions, gadgets or options from all sources I can find and adapt. Be sure to always use an official firmware for flying in real world. Maybe you could try the OLDEST available build

![TravisLogo](/TravisCI-Mascot-2.png)

[![Build Status](https://travis-ci.com/derdoktor667/Flysky-OpenTX-Test-Branch.svg?branch=derdoktor667%2Fnv14-rebuilding)](https://travis-ci.com/derdoktor667/Flysky-OpenTX-Test-Branch)

**This is _not affiliated_ with Flysky / uFPV or anyone else.**

You can use the included Dockerfile to create your own firmware.

### Building

1. Install Docker

2. Clone the repo

   `git clone https://github.com/derdoktor667/Flysky-OpenTX-Test-Branch`

3. Pull the container:

   `docker pull derdoktor667/nv14-build:latest`

4. Run the container, specifying the path to the repo as a mount volume:

   `docker run --rm -it -v [YOUR-REPO-PATH]:/nv14-build derdoktor667/nv14-build`

   For example (Windows):

   `docker run --rm -it -v "X:/Github/Flysky-OpenTX-Test-Branch:/nv14-build" derdoktor667/nv14-build`

The compiled firmware image will be placed in the build of the source directory when the build has finished.  

### Languages

Not working yet. **Only** English at the moment.

### Changing the build flags

Build flags can be passed as a switch to the Docker container command.

The syntax is `-e "CMAKE_FLAGS=SWITCH01=VALUE01 SWITCH02=VALUE02"`.

Defaults will be overwritten or created.

### Examples

1. Build from the source in `X:/Github/Flysky-OpenTX-Test-Branch` and enable `HELI`:

   `docker run --rm -it -v "X:/Github/Flysky-OpenTX-Test-Branch:/nv14-build" -e "CMAKE_FLAGS=HELI=YES" derdoktor667/nv14-build`

### Native

Clone the repo, create a cmake workdir and try possible build command:

`cmake -DGVARS=OFF -DLUA=ON -DLUA_COMPILER=ON -DPCB=NV14 -SIMU_AUDIO=OFF -DSIMU_LUA_COMPILER=OFF -DUSB_SERIAL=ON -DHELI=OFF -DMULTIMODULE=ON -DALLOW_NIGHTLY_BUILDS=ON -DAUTOSWITCH=ON -DAUTOSOURCE=ON -DGUI=YES -DBOOTLOADER=NO -DCMAKE_BUILD_TYPE=Release../`

best regards

### _derdoktor667_
