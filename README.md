# Multi Functional Rescue Rover Project

This repository is a versioned workspace for a rescue rover / nature rover platform built around Arduino-based firmware, mobile-app control, sensing, robotic-arm actuation, water-pump support, line following, obstacle avoidance, and supporting controller assets.

It is not a single sketch repo. The top level preserves multiple dated revisions of the rover, older multi-microcontroller source trees, Android controller files, App Inventor projects, wiring references, and a later standalone motor test sketch.


## 🎥 Featured Demo

[![Watch the demo](https://img.youtube.com/vi/Pc90v19VqbE/maxresdefault.jpg)](https://www.youtube.com/watch?v=Pc90v19VqbE)

▶️ Click the image to watch the video on YouTube

## Project Summary

Across the folders in this repository, the rover evolves through these capabilities:

- Differential-drive movement for a 4-wheel rover
- Robotic arm control with multiple joints and a gripper
- Obstacle avoidance using ultrasonic sensors
- Line following using an IR sensor array on a deployable servo mount
- Environmental and system sensing, including DHT22, MQ-4, LDR, voltage, and current sensing
- OLED status/debug display
- Water pump and aiming laser control
- Lighting control and experimental light patterns
- Bluetooth / serial command control from a custom mobile app
- PictoBlox-based input handling in one intermediate version
- Archived camera and timelapse support from an older ESP32-CAM-based architecture

## Top-Level Repository Overview

The root folder is best understood as a timeline of rover builds plus supporting artifacts.

| Path | What it contains | Notes |
| --- | --- | --- |
| `1.0_3-21-24_Nature_Rover_Basic_Setup/` | First Mega-based baseline sketch with drive, arm, obstacle avoidance, line following, and sensors | Good reference for the initial integrated Arduino Mega migration |
| `1_0_3_21_24_Nature_Rover_Basic_Setup_copy_20240323213043/` | Snapshot copy of the initial setup | Preserved backup / working copy |
| `21_1_2026_FUSION_1200KV_motor_testing_code/` | Small standalone ESC/BLDC test sketch using `Servo` to send microsecond PWM | Separate from the main rover firmware |
| `MFRR_Differentiatl_Drive_Version.aia` | MIT App Inventor project source for a rover controller app | Root-level mobile-app source artifact |
| `Source from the previous version of the project/` | Archived older generation of the project | Contains multi-microcontroller firmware, app packages, and notes |
| `V2_3-28-24_Nature_Rover_Introducing_BTS_motor_driver/` | Version introducing a BTS motor-driver arrangement / motor-control rewiring | The current `.ino` acts like a simple motion test loop |
| `V3_3_28_24_Nature_Rover_Arm_control/` | Integrated Mega sketch adding stronger arm control, OLED, and pump support | Early mature integrated build |
| `V3_3_28_24_Nature_Rover_Arm_control_copy_20240404202554/` | Snapshot copy of V3 | Preserved backup |
| `V4_3_28_24_Nature_Rover_Pictoblox_Control/` | V3-style build plus PictoBlox/ESP input handling | Adds `PictobloxControl.h` and extra pin notes |
| `V5_4-21-24_Nature_Rover_PrecisionArmControl/` | Refined arm control using servo arrays and cleaner state handling | Includes Android controller app source inside the folder |
| `V6_4_27_24_Nature_Rover_Extended_Upgrade/` | Most complete stable integrated rover build in the repo | Adds lighting, richer OLED pages, pump laser handling, and extra project assets |
| `Zzz_Nature_Rover_Under_Construction_Version/` | Experimental continuation of V6 | Adds app-message display support and experimental lighting patterns |
| `README.md` | This project guide | Repository-level documentation |

Hidden Git metadata also exists at the root as `.git/`, but it is omitted from the table above because it is repository infrastructure rather than project content.

## Archived Previous-Version Source Tree

The `Source from the previous version of the project/` folder preserves an earlier architecture that split responsibility across several boards.

### Contents of the archive

| Path | Purpose |
| --- | --- |
| `Source from the previous version of the project/Controller essentials/` | Android controller deliverables, including `MFCC_V2.apk` and `MFCC_V2.aab` |
| `Source from the previous version of the project/MC0_Arduino_Uno/` | Main rover controller firmware for the older UNO-based build |
| `Source from the previous version of the project/MC1_Arduino_Nano/` | Sensor-side microcontroller sketch |
| `Source from the previous version of the project/MC2_ESP8266/` | Peripheral/display microcontroller code |
| `Source from the previous version of the project/MC3_ESP32CAM/` | Camera/timelapse firmware, including a version that sends IP information over software serial |
| `Source from the previous version of the project/Version note and documentations/` | Architecture notes and documentation text files |

### What the older architecture did

The version notes in the archive describe the older board split like this:

- `MC0_Arduino Uno`: main rover control, robotic arm, wheels, obstacle avoidance, Bluetooth app communication, and inter-controller communication
- `MC1_Arduino Nano`: sensor acquisition node
- `MC2_ESP8266`: OLED/peripheral display handling
- `MC3_ESP32CAM`: camera and timelapse support

That archived source is useful if you want camera support or want to study how the project looked before it was consolidated onto an Arduino Mega-based workflow.

## Version Evolution

The repository naming is date-heavy, but there is a clear progression through the versions.

| Version / folder | Main idea |
| --- | --- |
| Older archived project | Multi-controller architecture using UNO, Nano, ESP8266, and ESP32-CAM |
| `1.0_3-21-24_Nature_Rover_Basic_Setup` | Early integrated Mega build with core rover movement, arm, obstacle avoidance, line following, and sensor streaming |
| `V2_3-28-24_Nature_Rover_Introducing_BTS_motor_driver` | Motor-driver revision and movement testing |
| `V3_3_28_24_Nature_Rover_Arm_control` | Better integrated arm control, OLED initialization, line-follower setup, and pump control |
| `V4_3_28_24_Nature_Rover_Pictoblox_Control` | Adds PictoBlox input combinations using dedicated pins |
| `V5_4-21-24_Nature_Rover_PrecisionArmControl` | Servo-array-based arm control and more structured arm state management |
| `V6_4_27_24_Nature_Rover_Extended_Upgrade` | Expanded features: laser-assisted pump handling, OLED debug pages, light initialization, app source, and wire-labeling sheet |
| `Zzz_Nature_Rover_Under_Construction_Version` | Experimental branch with app-driven OLED messages and multiple lighting modes/patterns |

## Which Folder Should You Start With?

If you are opening this project for the first time:

- Start with `V6_4_27_24_Nature_Rover_Extended_Upgrade/` if you want the most complete stable rover firmware in this repo
- Inspect `Zzz_Nature_Rover_Under_Construction_Version/` if you want the latest experimental ideas
- Use `1.0_3-21-24_Nature_Rover_Basic_Setup/` if you want the simplest Mega-based integrated baseline
- Open `Source from the previous version of the project/` only if you specifically need the legacy multi-board design, Android deliverables, or ESP32-CAM camera source
- Open `21_1_2026_FUSION_1200KV_motor_testing_code/` only for the separate ESC / brushless motor test

## Structure of the Newer Mega-Based Sketches

From V3 onward, each rover version is organized as a self-contained Arduino sketch folder with a main `.ino` file plus supporting headers. The newer integrated versions commonly include these modules:

| File | Responsibility |
| --- | --- |
| `WheelMotors.h` | Low-level wheel PWM control and helper movement functions such as `goForward()`, `goBackward()`, `goLeft()`, `goRight()`, and `Stop()` |
| `RoboticArm.h` | Servo declarations, arm geometry/state, rest/drop positions, and arm movement helpers |
| `ObstacleAvoidance.h` | Ultrasonic sensor pins, safe-distance settings, and collision-avoidance driving logic |
| `Line_follower.h` | IR array setup, deploy/retract servo behavior, thresholds, and line-follow algorithm |
| `Sensors.h` | Sensor power management plus voltage, current, DHT22, MQ-4, and LDR reading logic |
| `DisplayMechanism.h` | OLED display setup and, in later versions, light initialization and lighting behavior |
| `Pump.h` | Water pump and laser control pins and helper functions |
| `PictobloxControl.h` | V4-only helper for PictoBlox / ESP GPIO-based control inputs |
| `CodeGuidance.h` | Human-readable command notes, pin usage notes, and hardware comments |

This layout makes it easy to treat each version folder as an Arduino project snapshot. You open the folder’s `.ino` file in Arduino IDE and keep the local headers beside it.

## Main Features in the Newer Integrated Builds

The V5, V6, and experimental Zzz versions implement most of the rover’s current integrated capabilities.

### Drive modes

- Manual drive mode
- Obstacle avoidance mode
- Sensor streaming mode
- Line follower mode

### Robotic arm

- Multi-joint servo control
- Complementary left/right elbow servo-angle mapping
- Rest-position routine
- Drop-object routine
- Gripper open/close handling

### Sensor stack

- DHT22 temperature/humidity
- MQ-4 gas sensing
- LDR light sensing
- Battery/system voltage measurement
- Current measurement
- Ultrasonic distance sensing on multiple sides

### Operator feedback

- OLED title/debug pages
- Sensor and line-follower reading pages
- Robotic arm position page
- In the experimental Zzz branch, message display from the mobile app

### Utility systems

- Water pump output
- Laser aiming output
- Rover lighting
- Experimental automatic and patterned lighting modes in the Zzz branch

## Control Protocol

The Mega-based versions use short serial/Bluetooth command strings with the rough form:

```text
<action>:<value>.
```

Examples from the newer codebase:

| Command | Meaning |
| --- | --- |
| `f:150.` | Drive forward with PWM 150 |
| `b:150.` | Drive backward with PWM 150 |
| `l:120.` | Turn left |
| `r:120.` | Turn right |
| `m:1.` | Manual driving mode |
| `m:2.` | Obstacle avoidance mode |
| `m:3.` | Sensor-reading/streaming mode |
| `m:4.` | Line-follower mode |
| `u:<delta>` | Arm joint command |
| `v:<delta>` | Arm joint command |
| `w:<delta>` | Arm joint command |
| `y:<delta>` | Wrist command |
| `z:1.` | Close gripper incrementally in newer builds |
| `z:-1.` | Fully open gripper in newer builds |
| `p:0.` | Turn off pump and laser |
| `p:1.` | Turn on aiming laser only |
| `p:2.` | Turn on pump |
| `a:1.` | Take arm to rest position |
| `a:4.` | Move arm to object-drop position |
| `a:5.` | Cycle OLED debug pages |

There is also a numeric-setting pattern used for obstacle-avoidance tuning, where numeric action characters are mapped into the `oaSettingsValue[]` array.

## Hardware Notes

The later integrated versions are written for an Arduino Mega-based rover. The code comments and pin maps indicate support for:

- 4 drive-motor PWM channels
- A multi-servo robotic arm
- A deployable line-follower array
- Front, back, left, and right ultrasonic sensors
- OLED display over I2C
- DHT22, MQ-4, LDR, voltage, and current sensors
- Pump and laser outputs
- Several auxiliary LEDs

The older archived design, by contrast, uses multiple microcontrollers for different subsystems.

## Software and Library Dependencies

The sketches rely on Arduino libraries and third-party sensor/display libraries. Based on the headers in the repo, you should expect to install at least:

- `Servo`
- `SoftwareSerial`
- `Wire`
- `SPI`
- `DHT sensor library` / `DHT_U`
- `Adafruit GFX`
- `Adafruit SSD1306`
- `Adafruit BMP280`
- `MQUnifiedsensor`

Not every library is actively used in every version. For example, BMP280 setup code exists in the sensor module but is commented in later builds because the code notes mention initialization freezing the system.

## Development Workflow

### For a newer integrated rover build

1. Open one version folder such as `V6_4_27_24_Nature_Rover_Extended_Upgrade/` in Arduino IDE.
2. Open the matching `.ino` file from that folder.
3. Install the required libraries.
4. Select the appropriate board, typically Arduino Mega 2560 for the newer integrated versions.
5. Verify that the pin assignments match your current hardware.
6. Upload the sketch and use the custom controller app or a serial terminal to send commands.

### For the archived multi-controller build

1. Open the appropriate microcontroller folder under `Source from the previous version of the project/`.
2. Build and flash each board independently.
3. Match board choice to the folder name: UNO, Nano, ESP8266, or ESP32-CAM.

## App and Controller Assets

This repository also stores controller-side materials, not just firmware.

- `MFRR_Differentiatl_Drive_Version.aia`: root-level MIT App Inventor project source
- `V5_4-21-24_Nature_Rover_PrecisionArmControl/Controller Android app/MFCC_V3.aia`: controller project source packaged with V5
- `V6_4_27_24_Nature_Rover_Extended_Upgrade/MFCC_V3.aia`: controller source placed beside the V6 firmware
- `Zzz_Nature_Rover_Under_Construction_Version/MFCC_V3.aia`: controller source for the experimental branch
- `Source from the previous version of the project/Controller essentials/MFCC_V2.apk`: packaged Android app
- `Source from the previous version of the project/Controller essentials/MFCC_V2.aab`: Android App Bundle

## Wiring and Documentation Artifacts

Several versions include auxiliary documentation files that are useful during hardware assembly and debugging:

- `ESP Pins.  Activated State  Arduino.txt`
- `MFRC wire labelling.xlsx`
- `Version note.txt`
- `Vero board shield essentials..txt`

Many `Version details.txt` files exist alongside the sketches, but several of them are currently blank and appear to have been kept as placeholders for future notes.

## Observations and Known Quirks

- Folder names are intentionally date-stamped and versioned; this repo preserves snapshots rather than aggressively cleaning history
- Some versions are copies/backups, not distinct feature branches
- `V2_3-28-24_Nature_Rover_Introducing_BTS_motor_driver` currently behaves more like a motor test than a full interactive build because much of the serial-command loop is commented out
- The experimental `Zzz_Nature_Rover_Under_Construction_Version` extends V6 but should be treated as work in progress
- Some command notes in `CodeGuidance.h` are aspirational; the actual `.ino` implementation should be treated as the source of truth

## Recommended Reading Order

If you want to understand the project quickly, this order works well:

1. Read `V6_4_27_24_Nature_Rover_Extended_Upgrade/V6_4_27_24_Nature_Rover_Extended_Upgrade.ino`
2. Read the companion headers in the same folder
3. Compare with `Zzz_Nature_Rover_Under_Construction_Version/` to see ongoing experiments
4. Explore `Source from the previous version of the project/` if you need historical context or camera support

## Why This Repo Is Valuable

This repository is useful not only as source code for the latest rover build, but also as an engineering history of the platform. It captures:

- hardware migration from a distributed architecture to a Mega-based integrated rover
- evolution of the controller app
- multiple experiments in arm mechanics and motion control
- sensor, display, lighting, and pump integrations
- archived camera/timelapse work that can inform a future rescue-rover rebuild

If you want the most practical starting point today, begin with `V6_4_27_24_Nature_Rover_Extended_Upgrade/`. If you want the newest ideas that are still being refined, inspect `Zzz_Nature_Rover_Under_Construction_Version/`.
