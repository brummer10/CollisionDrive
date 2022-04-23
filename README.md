# CollisionDrive.lv2
Overdrive/Distortion

![CollisionDrive](https://github.com/brummer10/CollisionDrive/blob/main/CollisionDrive.png?raw=true)


## Features

- Overdrive/Distortion simulation. 

CollisionDrive is modeled after the Horizon Devices Precision Drive(*), a modern overdrive pedal with a built-in noise gate.

Besides the usual Volume and Drive controls, the CollisionDrive features Attack and Bright controls.

The Attack control manipulates the response of the pedal, turning it down simultaneously softens the overdrive attack and increases the sustain.

The Bright control gives you even more flexibility. It can add presence to darker sounding amps, or remove buzzing when needed.

The Gate control sets the noise gate threshold. In the plugin interface, this control lights up to indicate that the noise gate is active.


(*) 'Other product names modeled in this software are trademarks of their respective companies that do not endorse and are not associated or affiliated with this software.
Horizon Devices Precision Drive is a trademark or trade name of another manufacturer and was used merely to identify the product whose sound was reviewed in the creation of this 
product. All other trademarks are the property of their respective holders.'

## Dependencys

- libcairo2-dev
- libx11-dev

## Binary

![example workflow](https://github.com/brummer10/CollisionDrive/actions/workflows/build.yml/badge.svg)

[CollisionDrive.lv2.zip](https://github.com/brummer10/CollisionDrive/releases/download/Latest/CollisionDrive.lv2.zip)

## Build

- git submodule init
- git submodule update
- make
- make install # will install into ~/.lv2 ... AND/OR....
- sudo make install # will install into /usr/lib/lv2
