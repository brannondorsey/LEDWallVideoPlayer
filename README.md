# LED Wall Video Player

This project is compatible with OF v0.8.4.

## Video Wall

### Hardware

The Moment installation consists of two large walls made up of 4 x 2 __modules__ of 36 cubes each (6 x 6). This makes the "resolution" of each wall 24 x 12. Each wall can function independently of the other, however, this video wall application treats them as a pair with a combined "resolution" of 48 x 12.

Each module has 36 cubes filled with 16-40 Adafruit NeoPixel LEDs daisy chained together into four separate strips. These four strips each share one data connection. All LEDs in each module share one 12V 60A power connection as well as a common ground (with the exception of the third module from the left on the right wall (B3) which shares a power supply connection with the module directly above it and the module directly to its right). Each module has 5 Fadecandy chips, 4 of which provide data output from all of their output pins (providing data to 8 cubes each) and 1 of which provides data from only half of its output pins (output to 4 only cubes). There are 120 Fadecandies in total.

Two Raspberry Pis and one wireless router rest behind each wall. One RPi controls the left 144 cubes (12x12, i.e. 2 x 2 modules) and the other controls the right 144 cubes of each wall. The Raspberry Pis are connected via ethernet to their respective wall's router and the two routers are bridged to create one LAN. Each Raspberry Pi is connected via USB to a 10-1 powered USB hub to allow it to connect to the 20 Fadecandies on each 1/4 of each wall.

### Software

#### Network Info

```
# Master Router, running DHCP server
SSID: Moment
IP: 192.168.2.1
Subnet: 255.255.255.0

# Bridged Router, not running DHCP
SSID: Moment Extender # Hidden SSID, not broadcasted
IP: 192.168.2.2

# Left Wall Left RPi
IP: 192.168.2.100 # static IP

# Left Wall Left RPi
IP: 192.168.2.101 # static IP

# Right Wall Left RPi
IP: 192.168.2.103 # static IP

# Right Wall Right RPi
IP: 192.168.2.102 # static IP

# Alienware CPU running OF Video Player Server
IP: 192.168.2.150 # (will be assigned this static IP upon next router reset, currently 192.168.2.104)
```

#### Applications + Scripts

All applications and scripts are located in `~/src/of_v0.8.4_linux64_release/apps/dolby/WallVidePlayer/bin`

- `LEDWallVideoPlayer`: LED Video Player. Loads video dependent on the weekday (see `data/weekdays` or `<video>` tag at path specified in `data/settings.xml`). This app is configured to automatically exit if it cannot reach the Raspberry Pis, so make sure you are on the "Moment" network and that all Raspberry Pis are running Fadecandy servers on port `7890` __or the app will crash__.
- `LEDWallClearPixels`: Turns all Pixels off (writes 0, 0, 0 to each) and then exits.
- `start_installation.sh`: Startup script that runs every weekday morning from at 7AM (Pacific time). It reboots all Raspberry Pis, waits 2 minutes for them to come back online, and then launches `LEDWallVideoPlayer` if it is not already running. This script is run via a crontab.
- `poll_installation.sh`: Launches `LEDWallVideoPlayer` if it is not currently running. This script is run every minute between 7AM-6PM on weekdays via a crontab.
- `stop_installation.sh`: Closes `LEDWallVideoPlayer` if it is running and then runs `LEDWallClearPixels` to turn LEDs off.

To edit scripts automated by crontab run `crontab -e`.

__Note:__ When running any script or app remotely that attempts to launch a GLFW Window (`LEDWallVideoPlayer` or `start_installation.sh`) you must first export the environment variable `DISPLAY=:0` (e.g. `DISPLAY=:0 ./LEDWallVideoPlayer`).

#### Fadecandy Servers and Pixel Mapping

Each RPi has a fadecandy server located in `/usr/local/bin` (don't edit the one in `~/`) that is automatically run at startup via `/etc/rc.local`. This server loads the `/usr/local/bin/fcserver.json` configuration file and listens for TCP connections on port `7890`. Pixel mapping is complete for the most part, however, there are a few errors that I noticed on each wall. To whoever works on Dolby project next, I suggest correcting the errors. Copies of each config file reside in this repo in `pixel_maps` and some info about mapping is available in [this Adafruit tutorial](https://learn.adafruit.com/1500-neopixel-led-curtain-with-raspberry-pi-fadecandy/fadecandy-server-setup). A mapping utility app exists for this project as well. [Email me](mailto:brannon@brannondorsey.com) and I will send it to you with a description of how it can be used.

#### Adapting LEDWallVideoPlayer

The LEDWallVideoPlayer code (in `~/src`) is compatible with OpenFrameworks v0.8.4. The only addon used is `ofxXmlSettings` (which is included in the OF distribution). Digging through the source code will probably be helpful in understanding how the application works, but the bulk of the logic happens in `FadeCandyController::update(ofPixels& pixels)`. Any 480 x 120 `ofPixels` instance (or 4:1 aspect ratio `ofPixels` object) should work smoothly, so if you wan't to hack up the source code to make something cooler than a video player, that is the function you would call to write to the two LED walls.

__Note:__ If you are using OS X the LEDWallVideoPlayer Xcode project file is named `videoPlayer2.xcodeproj`. This is a product of copying an old project and I never got around to renaming it.


