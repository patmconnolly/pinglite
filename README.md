# PingLite

## About

This project was began as monitoring of the uptime of a thing need not be a big ordeal. It simply needs to be watched passively from somewhere else.
Using this as our frame of reference we can break down what exactly we want from here.

The name PingLite was chosen, as monitoring can be as simple and lightweight as a ping. No fancy UI, no extra paid utilities, just simple config and monitor.

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

1. Define configuration files for what to monitor.
2. Create function call for testing.
3. Add functionality for pinging.
4. Add functionality for retcode.
5. Add functionality for SSL Certs
6. Define data file for info needed to alert on next run if applicable.
7. Create API handler.
8. Create other handlers as needed.

*Other to-do's to be added as needed*

## Documentation

Documentation should be created as the product is developed. Ideally hosted in this repository.

In time, the domain name purchased for this product will be used.

[PingLite.xyz](https://pinglite.xyz)
