# ZenBot

C++ | C | Arduino | IoT

> Alpha release

This repository include a arduino project, compatible with:

- Adafruit Metro M0 Express.
- Adafruit BME680.
- Adafruit WINC1500 WIFI Shield.
- MCUFriends 2.8" TFT LCD Shield.

## Current features

- On screen metrics of BME680 using MCUFriends TFT Shield.
- On screen network details of WINC1500 using Adafruit WIFI Shield.

## Planned features

- Sync data with backend project, including dashboard metrics.

## v.1.0 - TODO 

- [ ] Refactor TFT Shield implementation using `screen.h` file.
- [ ] Add `sync.h` file ...
    - [ ] Add batchUpload method to send a HTTP with encrypted payload.
    - [ ] Add encryptData method to convert payload into non-readable human data.
    - [ ] Add sendRequest method to create a HTTP request instance with custom URL and headers.
- [ ] Add Authorization header on arduino secrets.
- [ ] Implement `sync.h` library.
- [ ] Disable on boot stuck logic of setup when sensor, or screen or shield isn't available.
- [ ] Add issue template for support requirement.
