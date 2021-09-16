# Welcome to PrISUm Software Development Kit!
This repository contains the development kit for building code for the car moving forward. This contains the new software library along with the build scripts needed to actually program the boards.

### New benefits
 - Use many different programmers (BlackMagic Probe, Built-in CMSIS-DAP on development boards, ATMEL-ICE...) 
 - More control over how the compute behaves
 - Much more in-depth knowledge of how these computes actually behave and many interesting features that we didn't actually know existed
 

### Getting Started
 - Download VS Code (https://code.visualstudio.com)
 - Clone this repository somewhere on your computer. All new software will be contained in this folder.
 - Open the folder with VS Code (Either drag the folder onto the VS Code application or open VS Code and select `Open Folder...`)
 - VS Code will prompt you to install some recommended extensions. Do so, it should install PlatformIO, C/C++ tools, and multisrc.
 
### Usage Guide
 - The `sources` folder is for you to put actual board code repositories. When you need to clone a software repo, clone it into this folder. It must be in this folder and no other folder.
 - If you look in the bottom corner of VS Code, there is a little button in the bottom toolbar `< something >`. This is the current project you are working on and refers to a folder in the sources folder.
 - As a first example, click on it and select `x_blinky`. Examples will always start with `x_` and you should never make a folder start with `x_` that is not an example.
 - Now, in the bottom left there is a checkmark (Build only) and a right arrow (Build and upload to board).
 - For debugging, use the bug/play icon in the left toolbar and click the green play button. 
 
### More details coming...
