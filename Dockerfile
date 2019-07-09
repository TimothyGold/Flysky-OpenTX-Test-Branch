# Ubuntu image for compiling OpenTX NV14

# disco
FROM ubuntu:disco

# now under new "LABEL"
LABEL maintainer="derdoktor667@gmail.com"

# root needed for docker
USER root

# have a nice day
ENV DEBIAN_FRONTEND noninteractive

# /bin/sh points to Dash by default, reconfigure to use bash until Android
# build becomes POSIX compliant
RUN echo "dash dash/sh boolean false" | debconf-set-selections && dpkg-reconfigure -p critical dash

# we run this

# enlight heavy docker image
# RUN apt-get -y update && apt-get -y dist-upgrade && apt-get -y install apt-utils build-essential cmake gcc git lib32ncurses6 lib32z1 libfox-1.6-dev libsdl1.2-dev qt5-default qtmultimedia5-dev qttools5-dev qttools5-dev-tools libqt5svg5-dev software-properties-common wget zip python-pip python-pil libgtest-dev git ruby-dev gcc-arm-none-eabi

  RUN apt-get -y update && apt-get -y dist-upgrade && apt-get -y install apt-utils build-essential cmake gcc git lib32ncurses6 libfox-1.6-dev gcc-arm-none-eabi

# smaller image
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# repo tool
ADD https://commondatastorage.googleapis.com/git-repo-downloads/repo /usr/local/bin/
RUN chmod 755 /usr/local/bin/*

# Set the working directory
WORKDIR /nv14-build

# Declare the mount point
VOLUME /nv14-build

ENV PATH $PATH:/nv14-build/radio/util
ENV PATH $PATH:/nv14-build/tools

ARG OPENTX_VERSION_SUFFIX=
ENV OPENTX_VERSION_SUFFIX ${OPENTX_VERSION_SUFFIX}

# Copy the build scripts to workdir
# COPY ${WORKDIR}/tools/utilize_docker.py ${WORKDIR}/buildit/utilize_docker.py

# build by script
ENTRYPOINT ["bash", "-c", "python3 /nv14-build/tools/utilize_docker.py $CMAKE_FLAGS"]
