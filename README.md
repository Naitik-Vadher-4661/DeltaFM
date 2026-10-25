# DeltaFM
A TUI based File Manager Written in c++ 


## ScreenShots 


<img width="1366" height="768" alt="Screenshot from 2026-10-24 22-42-54" src="https://github.com/user-attachments/assets/edbce2a6-25f7-4f48-85e4-bbb4a4bef869" />

                                                                                                                 
                                                                                                                 
                                                                                                                 
 
                                                                                                                       
<img width="1351" height="750" alt="Screenshot from 2026-10-24 22-43-48" src="https://github.com/user-attachments/assets/d2a5a1bc-8677-4982-930a-d09e138582a1" />

                                                                                                                
                                                                                                                       
                                                                                                                       
# Installation

## Pre-built Binary(Recommanded)
 use dfm command to use DeltaFM after installing it
 
### For Arch/Cachy
```
sudo pacman -S --needed file
curl -fL -o DeltaFM https://github.com/Naitik-Vadher-4661/DeltaFM/releases/download/Deltafm/DeltaFM_linux
chmod +x DeltaFM
sudo mv DeltaFM /usr/local/bin/dfm
dfm
```

### For ubuntu/Debian
```
sudo apt update
sudo apt install -y libmagic1
curl -fL -o DeltaFM https://github.com/Naitik-Vadher-4661/DeltaFM/releases/download/Deltafm/DeltaFM_linux  
chmod +x DeltaFM
sudo mv DeltaFM /usr/local/bin/dfm
dfm
```

### For MacOS
```
brew install libmagic
curl -fL -o DeltaFM https://github.com/Naitik-Vadher-4661/DeltaFM/releases/download/Deltafm/DeltaFM_mac
chmod +x DeltaFM
xattr -d com.apple.quarantine DeltaFM 2>/dev/null
sudo mv DeltaFM /usr/local/bin/dfm
dfm
```

### for Windows
```
vcpkg install libmagic:x64-windows
mkdir C:\DeltaFM\bin
curl.exe -fL -o C:\DeltaFM\bin\dfm.exe https://github.com/Naitik-Vadher-4661/DeltaFM/releases/download/Deltafm/DeltaFM.exe
[Environment]::SetEnvironmentVariable("Path", [Environment]::GetEnvironmentVariable("Path","User") + ";C:\DeltaFM\bin", "User")
```
Close PowerShell, open a new one and  run `dfm`.

 ## Compile from source 
 #### Arch / CachyOS
 ```
 sudo pacman -Syu
 sudo pacman -S --needed base-devel cmake git file
 git clone https://github.com/Naitik-Vadher-4661/DeltaFM.git
 cd DeltaFM
 cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
 cmake --build build --parallel
 sudo cmake --install build
 dfm
 ```
 
 #### Ubuntu / Debian
 ```
 sudo apt update
 sudo apt install -y build-essential cmake git libmagic-dev
 git clone https://github.com/Naitik-Vadher-4661/DeltaFM.git
 cd DeltaFM
 cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
 cmake --build build --parallel
 sudo cmake --install build
 dfm
 ```
 
 #### macOS

 ```
 brew install cmake git libmagic
 git clone https://github.com/Naitik-Vadher-4661/DeltaFM.git
 cd DeltaFM
 cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
 cmake --build build --parallel
 sudo cmake --install build
 dfm
 ```
 
 #### Windows (PowerShell)

 You have to have vcpkg installed if not use this
 ```
 git clone https://github.com/microsoft/vcpkg C:\vcpkg
 C:\vcpkg\bootstrap-vcpkg.bat
 C:\vcpkg\vcpkg install libmagic:x64-windows

 ```

 DeltaFM for windows
 ```
 vcpkg install libmagic:x64-windows
 git clone https://github.com/Naitik-Vadher-4661/DeltaFM.git
 cd DeltaFM
 cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows
 cmake --build build --config Release --parallel
 cmake --install build --config Release --prefix C:\DeltaFM
 copy build\Release\*.dll C:\DeltaFM\bin\
 [Environment]::SetEnvironmentVariable("Path", [Environment]::GetEnvironmentVariable("Path","User") + ";C:\DeltaFM\bin", "User")
 ```


# Uninstallation

#### Arch / CachyOS
```
sudo rm /usr/local/bin/dfm
```

#### Ubuntu / Debian
```
sudo rm /usr/local/bin/dfm
```


#### macOS
```
sudo rm /usr/local/bin/dfm
```

#### Windows (PowerShell)
```
$p = [Environment]::GetEnvironmentVariable("Path","User") -split ';' | Where-Object { $_ -ne 'C:\DeltaFM\bin' }
[Environment]::SetEnvironmentVariable("Path", ($p -join ';'), "User")
Remove-Item -Recurse -Force C:\DeltaFM
```
The first two lines remove `C:\DeltaFM\bin` from your PATH, and the last one deletes the folder. Open a new terminal afterwards. 



If you built from source, you can also delete the cloned `DeltaFM` folder.
