# [Smooch](http://www.smooch.io)

[![Pod Version](http://img.shields.io/cocoapods/v/Smooch.svg)](http://cocoadocs.org/docsets/Smooch/)
[![Platform](http://img.shields.io/cocoapods/p/Smooch.svg)](http://cocoadocs.org/docsets/Smooch/)
[![License](http://img.shields.io/cocoapods/l/Smooch.svg)](http://smooch.io/terms.html)
[![Carthage compatible](https://img.shields.io/badge/Carthage-compatible-4BC51D.svg?style=flat)](https://github.com/Carthage/Carthage)

Smooch is the best way to have personal, rich conversations with people on your website or customers on any device. Our features, integrations and developer-friendly APIs empower companies to connect with their customers in a whole new way.

The Smooch iOS SDK will add [in-app messaging](https://smooch.io/in-app-messaging/) to your iOS app. Customers will be able to talk to you from your app, while you manage conversations using your favorite business apps.

- Maximize development productivity with a single codebase across platforms and [add more channels](https://smooch.io/cross-channel-messaging/) anytime.
- Build better relationships with messaging that feels and looks native to your app.
- Delight your customers with the most engaging conversational experience using [rich messaging](https://smooch.io/rich-messaging/).
- Sync conversations across every device and channel your customers use.
- Bring every conversation into your existing business apps. No new tool to learn. [See all integrations](https://smooch.io/integrations/).

Sign up and get an app id: [https://app.smooch.io/signup](https://app.smooch.io/signup).

CocoaPods:

    pod 'Smooch'
    pod update

Carthage:

    github "smooch/smooch-ios"
    carthage update

Obj-C:

```objc
[Smooch initWithSettings:[SKTSettings settingsWithAppId:@"YOUR_APP_ID"] completionHandler:^(NSError * _Nullable error, NSDictionary * _Nullable userInfo) {
        // Your code after init is complete
    }];
[Smooch show];
```

Swift:

```Swift
Smooch.initWith(SKTSettings(appId: "YOUR_APP_ID")) { (error: Error?, userInfo: [AnyHashable : Any]?) in
            // Your code after init is complete
        }
Smooch.show()
```

Our [Docs and full install guide](http://docs.smooch.io).

Also, check out [Smooch Help Kit](https://github.com/smooch/smooch-helpkit-ios) for even more features!
