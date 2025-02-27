# PingLite

## About

This project was began as monitoring of the uptime of a thing need not be a big ordeal. It simply needs to be watched passively from somewhere else.
Using this as our frame of reference we can break down what exactly we want from here.

The name PingLite was chosen, as monitoring can be as simple and lightweight as a ping. No fancy UI, no extra paid utilities, just simple config and monitor.

## Downloads and Installing

### Downloads

GitHub has the capability to download the whole repo, if you wish to just have the product as a package you may visit the hosted download page for PingLite.

[PingLite Downloads](https://download.pinglite.xyz/pinglite/)

### Installation

To install system wide, simply unzip the downloaded packages to the root directory as SU:

```
sudo tar -xvf ./pinglite-<BRANCH>-<VERSION>.tar -C /
```

This will create the appropriate directories:
- usr
  - bin
    - pinglite _executable_
  - lib
    - pinglite _folder_
- var
  - lib
    - pinglite _folder_

The executable `pinglite` is the only thing entering in the shared folder, the usr/lib and var/lib folders will have a pinglite folder to store those items separate from other things on the node.

Non-default paths and custom installs are on the roadmaps.

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

1. ~~Define configuration files for what to monitor.~~ _Complete_
2. Basic infrastructure for releases and testing. _In Progress_
3. Non-default paths and custom installs.
4. Create function call for testing.
5. Add functionality for pinging.
6. Add functionality for retcode.
7. Add functionality for SSL Certs
8. Define data file for info needed to alert on next run if applicable.
9. Create API handler.
10. Create other handlers as needed.

*Other to-do's to be added as needed*

## Documentation

Documentation should be created as the product is developed. Ideally hosted in this repository.

In time, the domain name purchased for this product will be used.

[PingLite.xyz](http://pinglite.xyz)
