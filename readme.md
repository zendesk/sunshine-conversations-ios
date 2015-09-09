# [SupportKit](http://www.supportkit.io)

[![Pod Version](http://img.shields.io/cocoapods/v/SupportKit.svg)](http://cocoadocs.org/docsets/SupportKit/)
[![Platform](http://img.shields.io/cocoapods/p/SupportKit.svg)](http://cocoadocs.org/docsets/SupportKit/)
[![License](http://img.shields.io/cocoapods/l/SupportKit.svg)](http://supportkit.io/terms.html)

Sign up and get an app token: [https://app.supportkit.io/signup](https://app.supportkit.io/signup).

CocoaPods:

    pod 'SupportKit'
    pod update
    
Obj-C:
    
    [SupportKit initWithSettings:[SKTSettings settingsWithAppToken:@"YOURAPPTOKEN"]];
    [SupportKit show];
    
Swift:

    SupportKit.initWithSettings("YOURAPPTOKEN")
    SupportKit.show()

Our [Docs and full install guide](http://docs.supportkit.io).