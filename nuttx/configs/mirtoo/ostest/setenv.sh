#!/bin/bash
# configs/mirtoo/ostest/setenv.sh
#
#   Copyright (C) 2012 Gregory Nutt. All rights reserved.
#   Author: Gregory Nutt <gnutt@nuttx.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name NuttX nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

if [ "$_" = "$0" ] ; then
  echo "You must source this script, not run it!" 1>&2
  exit 1
fi

if [ -z "${PATH_ORIG}" ]; then export PATH_ORIG="${PATH}"; fi

WD=`pwd`
if [ ! -x "setenv.sh" ]; then
  echo "This script must be executed from the top-level NuttX build directory"
  exit 1
fi

# This the Cygwin path to the location where I installed the MicroChip
# PIC32MX C32 toolchain under windows.  This is *not* the default install
# location so you will probably have to edit this.  You will also have
# to edit this if you install a different version of if you install the
# toolchain at a different location
export TOOLCHAIN_BIN="/cygdrive/c/MicroChip/mplabc32/v1.12/bin"

# This the Linux path to the location where I installed the MicroChip
# PIC32MX XC32 toolchain under Linux.  This is the default install
# location.  You will also have to edit this if you install a different
# version of if you install the toolchain at a different location
#export TOOLCHAIN_BIN="/opt/microchip/xc32/v1.00/bin"

# This the Cygwin path to the location where I installed the Pinguino
# toolchain under Windows.  You will have to edit this if you install the
# tool chain in a different location or use a different version.  /bin
# needs to precede the tool path or otherwise you will get
# /cygdrive/c/PinguinoX.3/win32/p32/bin/make which does not like POSIX
# style paths.
#export TOOLCHAIN_BIN="/bin:/cygdrive/c/PinguinoX.3/win32/p32/bin"

# This the Linux path to the location where I installed the microchipOpen
# toolchain under Linux.  You will have to edit this if you use the
# microchipOpen toolchain.
#export TOOLCHAIN_BIN="~/projects/microchipopen/v105_freeze/pic32-v105-freeze-20120622/install-image/bin"

# This is the path to the toosl subdirectory
export PIC32TOOL_DIR="${WD}/tools/pic32mx"

# Add the path to the toolchain to the PATH varialble
export PATH="${TOOLCHAIN_BIN}:${PIC32TOOL_DIR}:/sbin:/usr/sbin:${PATH_ORIG}"

echo "PATH : ${PATH}"
