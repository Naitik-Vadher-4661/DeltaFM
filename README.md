# DeltaFM
A TUI based File Manager Written in c++ 


## ScreenShots 

### DeltaFM main UI

<img width="1366" height="768" alt="Screenshot from 2026-11-02 20-51-45" src="https://github.com/user-attachments/assets/a25f1698-6a57-4f96-93e5-b1881d58db26" />

### Features

#### Delta Previewer and logs

<img width="1366" height="768" alt="Screenshot from 2026-11-02 20-52-03" src="https://github.com/user-attachments/assets/11fa9564-5149-46e8-8fc8-2c89a2f8c22f" />                                                                                                     

#### Creating File

<img width="1366" height="768" alt="Screenshot from 2026-11-02 20-52-28" src="https://github.com/user-attachments/assets/4d2f7c06-9715-4786-893f-e28b439d333b" />

#### Deleting File

<img width="1366" height="768" alt="Screenshot from 2026-11-02 20-52-52" src="https://github.com/user-attachments/assets/448fffb3-305e-4aa1-adfa-2a4e8887d570" />







                                                                                                                       
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
  sudo mkdir -p /usr/local/bin
  sudo mv DeltaFM /usr/local/bin/dfm
  dfm
```

### for Windows
```
$dir = "C:\DeltaFM\bin"
$zip = "$env:TEMP\DeltaFM_windows.zip"
New-Item -ItemType Directory -Force $dir | Out-Null
curl.exe -fL -o $zip https://github.com/Naitik-Vadher-4661/DeltaFM/releases/download/Deltafm/DeltaFM_windows.zip
Expand-Archive -Force $zip $dir
Move-Item -Force "$dir\DeltaFM.exe" "$dir\dfm.exe"
Remove-Item $zip
$p = [Environment]::GetEnvironmentVariable("Path","User")
if (($p -split ';') -notcontains $dir) { [Environment]::SetEnvironmentVariable("Path", "$p;$dir", "User") }
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
After vcpkg is installed or already installed compile from source 
```
git clone https://github.com/Naitik-Vadher-4661/DeltaFM.git
cd DeltaFM
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows
cmake --build build --config Release --parallel
cmake --install build --config Release --prefix C:\DeltaFM
copy build\Release\*.dll C:\DeltaFM\bin\

$dir = "C:\DeltaFM\bin"
$p = [Environment]::GetEnvironmentVariable("Path","User")
if (($p -split ';') -notcontains $dir) { [Environment]::SetEnvironmentVariable("Path", "$p;$dir", "User") }
 ```


# Uninstallation

#### Arch / CachyOS
```
sudo rm /usr/local/bin/dfm
sudo rm -rf "${XDG_STATE_HOME:-$HOME/.local/state}/deltafm"
```

#### Ubuntu / Debian
```
sudo rm /usr/local/bin/dfm
sudo rm -rf "${XDG_STATE_HOME:-$HOME/.local/state}/deltafm"
```


#### macOS
```
sudo rm /usr/local/bin/dfm
sudo rm -rf "$HOME/Library/Logs/DeltaFM"
```

#### Windows (PowerShell)
```
$p = [Environment]::GetEnvironmentVariable("Path","User") -split ';' | Where-Object { $_ -ne 'C:\DeltaFM\bin' }
[Environment]::SetEnvironmentVariable("Path", ($p -join ';'), "User")
Remove-Item -Recurse -Force C:\DeltaFM
Remove-Item -Recurse -Force "$env:LOCALAPPDATA\DeltaFM"
```
The first two lines remove `C:\DeltaFM\bin` from your PATH, and the last one deletes the folder. Open a new terminal afterwards. 



If you built from source, you can also delete the cloned `DeltaFM` folder.
