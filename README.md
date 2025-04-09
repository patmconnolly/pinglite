# PingLite

## About

This project was began as monitoring of the uptime of a thing need not be a big ordeal. It simply needs to be watched passively from somewhere else.
Using this as our frame of reference we can break down what exactly we want from here.

The name PingLite was chosen, as monitoring can be as simple and lightweight as a ping. No fancy UI, no extra paid utilities, just simple config and monitor.

## How To Configure Reporting

### API

In your config file, enter your complete URL to hit ubnder the `[API] URL` variable.

Your PAYLOAD can be whatever you want it to be, configure the JSON file in the `[API] PAYLOAD` variable.

Your available variables are as follows:

- `{{ HOST }}`
- `{{ HTTP_CODE }}`
- `{{ SSL_VALID }}`
- `{{ SSL_EXPIRY_DAYS }}`
- `{{ ALERT_STRING }}`

These strings are case sensitive and will be replaced on the fly with the appropriate string data for your payload.

It is recommended that when using as a CRON task, to be documented later, to use the `silent` flag to avoid over logging to a file that is not rotated.

## Downloads and Installing

### Downloads

GitHub has the capability to download the whole repo, if you wish to just have the product as a package you may visit the hosted download page for PingLite.

[PingLite Downloads](https://download.pinglite.xyz/pinglite/)

### Installation

To install system wide, simply unzip the downloaded packages to a directory and move the executable file `pinglite` to a place on the path:

```
sudo tar -xvf ./pinglite-<BRANCH>-<VERSION>.tar
```

### Versions

In the download directory there are three folders:

- development
  - Development is where active development is happening.
  - The versioning is: `pinglite-dev-<YYYY>.<MM>.<DD>-<HH>.<mm>.tar`
  - Only the most recent 20 builds will be kept, it is cleaned nightly.
- nightly
  - This is where the builds that compile and are submitted by EOD will be placed.
  - New features will be available before an actual release occurs.
  - Compiles automatically every night.
  - Only the most recent 50 builds will be kept, it is cleaned nightly.
  - The versioning is: `pinglite-nightly-<YYYY>.<MM>.<DD>.tar`
- stable
  - Stable and complete releases will be here, delayed release to ensure nothing wrong is happening.
  - Compiled on a manual timeframe and no automatic timer builds take place.
  - The versioning is: `pinglite-stable-<YYYY>.<MM>.<DD>.tar`

### Compiling

PingLite is compiled using Jenkins pipelines that trigger a docker container build. This is to ensure that the build of PingLite is as portable as possible.

From the root of the project, execute the following for a manual compile:

```
docker run --rm -v .:/usr/src/myapp -w /usr/src/myapp gcc:12 make
```

### Goals

For setup and testing purposes, we will have the following information checked:
- Does the URL provided resolve? (Y/N)

To hit a target URL with a single call and collect the following information:
- If Successfully Hit
- Return Code
- SSL Certificate Information

When to alert:
- On SSL expiry
  - Configurable early alert.
  - Configurable snooze time for reminders.
  - Recovery alerts if desired.
- If site is unreachable or return code is not as desired.
  - Alert immedietly upon change.
  - Configurable snooze time for reminders.
  - Recovery alerts.

How to alert:
- API call
- Email
- Other chat application options

### Scope

The scope will be limited to assuming a single call is being made, and if it has not been made before creating the appropriate data for future runs.
The wheel does not need to be recreated on a loop for constant processes, the timing of checks can be done by adding the single call to a CRON task.

## To-Do List:

The basic to-do list has been completed. Other handlers can be added as needed. Bugs will be fixed upon being notified.

## Outside expertice needed:

1. Review file and folder structure, adjust as needed.
2. Review code as written, adjust as needed.

*Other to-do's to be added as needed*

## Documentation

Documentation should be created as the product is developed. Ideally hosted in this repository.

In time, the domain name purchased for this product will be used.

[PingLite.xyz](http://pinglite.xyz)
