#!/usr/bin/env bash
set -ex

id
env
pwd

sudo apt update
sudo apt-get install -y --no-install-recommends apt-utils
sudo apt install -y wget unzip software-properties-common lsb-release openssh-client curl

# QT 5.15.2, is installed into /opt/qt515/
sudo touch /etc/apt/sources.list
sudo add-apt-repository -y ppa:beineri/opt-qt-5.15.2-$(lsb_release -cs)

# Latest cmake for current platform
sudo wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | sudo gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
sudo apt-add-repository -y "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"

# GCC 11
sudo add-apt-repository ppa:ubuntu-toolchain-r/test

sudo apt update
sudo apt install -y git cmake build-essential ninja-build \
    qt515declarative qt515serialport qt515charts-no-lgpl qt515svg \
    libgtk2.0-dev libgl-dev gcc-11 g++-11 libgtest-dev

sudo update-alternatives --remove-all cpp
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 110 --slave /usr/bin/g++ g++ /usr/bin/g++-11 --slave /usr/bin/gcov gcov /usr/bin/gcov-11 --slave /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-11 --slave /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-11 --slave /usr/bin/cpp cpp /usr/bin/cpp-11

sudo gcc --version && g++ --version && gcov --version
sudo update-alternatives --config gcc

# https://askubuntu.com/questions/616065/the-imported-target-qt5gui-references-the-file-usr-lib-x86-64-linux-gnu-li
sudo ln -f /usr/lib/x86_64-linux-gnu/libEGL.so.1 /usr/lib/x86_64-linux-gnu/libEGL.so

mkdir -p ~/bin
wget -c -nv "https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage" -O ~/bin/linuxdeploy
chmod a+x ~/bin/linuxdeploy

wget -c -nv "https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/continuous/linuxdeploy-plugin-qt-x86_64.AppImage" -O ~/bin/linuxdeploy-plugin-qt
chmod a+x ~/bin/linuxdeploy-plugin-qt

# QT GTK+ 2 Plugins
# https://github.com/probonopd/linuxdeployqt/issues/338
# https://github.com/probonopd/linuxdeployqt/issues/355
# https://github.com/probonopd/linuxdeployqt/issues/60
# cd /opt
# git clone http://code.qt.io/qt/qtstyleplugins.git
# cd qtstyleplugins
# /opt/qt515/bin/qmake
# make -j$(nproc)
# sudo make install
# rm -rf /opt/qtstyleplugins
