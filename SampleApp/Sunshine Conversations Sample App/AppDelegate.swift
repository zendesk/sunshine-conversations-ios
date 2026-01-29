//
// AppDelegate.swift
// Sunshine Conversations Sample App
//
// Created by Zendesk on 26/10/2021.
//
// Copyright © 2021 Zendesk. All rights reserved.
//
// By downloading or using the Zendesk Mobile SDK, You agree to the Zendesk Master
// Subscription Agreement https://www.zendesk.com/company/customers-partners/#master-subscription-agreement
// and Application Developer and API License
//
// Agreement https://www.zendesk.com/company/customers-partners/#application-developer-api-license-agreement and
// acknowledge that such terms govern Your use of and access to the Mobile SDK.


import UIKit

@main
final class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.

        SunshineConversationsWrapper.shared.initialize { error, userInfo in
            if let error = error {
                print("❌ Error initializing the Sunshine Conversations SDK: \(error.localizedDescription). Information: \(String(describing: userInfo?.description))")
            } else {
                print("🟢 Successfully initialized the Sunshine Conversations SDK.")
            }
        }
        return true
    }

}

