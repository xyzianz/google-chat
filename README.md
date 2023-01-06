# google-chat
A Qt6-based chat client for Google Chat 

## Build and install instructions

    PREFIX=/usr qmake6 google-chat.pro
    make all
    sudo make install

## Features
* Support for multiple profiles with the `--profile` command line argument
* Links open in your default browser
* Minimizes to System Tray Icon on close. Use the Quit action to quit (Typically `Ctrl-Q`)
* Show/hide using System Tray Icon
* Support for HiDPI Scaling using `QT_SCALE_FACTOR` environment variable
* Uses the lightweight Qt WebEngine, which is based on chromium. No 100+ Mb electron installation!
* Wraps the official Google Chat web client in a Qt Window, mostly natively

## Use

    # Start multiple profiles
    ./google-chat --profile "Test 1" &
    ./google-chat --profile "Test 2" &

    # Start with a different DPI
    QT_SCALE_FACTOR=1.43 ./google-chat

## Why a dedicated Google Chat client?
I needed to scratch my own itch...
