# Build guideline

Follow this document to build the application on your platform

## Tools
Qt libraries and Qt Creator Download the Qt for your platform Qt offline installer and install it. Visual studio 2017 or 2019 (for Windows)

 Notes: 
        Qt version 5.12 or higher is recommended
        Windows: Select compiler MSCV 2017 (or 2019) 64 - bit (or 32 bit depends on your OS)
 	Linux: Compiler GCC 64 or 32
 	MAC:   Compiler GCC 64 or 32 (macOS)
 	
## Setup
### Clone project and fetch submodules

	git clone https://github.com/nunchuk-io/tapsigner-tool.git
	cd tapsigner-tool
	git submodule update --init --recursive

### Build nunchuck-client-qt

	Open Qt Creator
        Open tapsigner-tool project via CMakeLists.txt
		Select your Kit (include compiler) : Desktop Qt %{Qt:Version} GCC 64bit,  (such as Desktop Qt 5.12.8 GCC 64bit)
		Run qmake
		Build
		...
        Run the application
