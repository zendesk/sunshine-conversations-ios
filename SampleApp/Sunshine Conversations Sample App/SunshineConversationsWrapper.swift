//
// SunshineConversationsWrapper.swift
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


import Foundation
import Smooch

final class SunshineConversationsWrapper {

    static let shared = SunshineConversationsWrapper()

    private let conversationDelegate = ConversationDelegate()
    private let authenticationDelegate = AuthenticationDelegate()

    deinit {
        Smooch.destroy()
    }

    func initialize(_ completion: @escaping (Error?, [AnyHashable: Any]?) -> Void) {
        #warning("Please enter your integrationId below.")
        let settings = SKTSettings(integrationId: "59aad4616082d43a0050a967")
    
        #warning("Customize your SDK settings below.")
        settings.conversationAccentColor = #colorLiteral(red: 0.9529411793, green: 0.6862745285, blue: 0.1333333403, alpha: 1)

        // Setup the authentication delegate.
        settings.authenticationDelegate = authenticationDelegate

        // Setup the conversation delegate.
        Smooch.update(conversationDelegate)

        Smooch.initWith(settings, completionHandler: completion)
    }

    func conversationViewController() -> UIViewController? {
        Smooch.newConversationViewController()
    }

    func conversationListViewController() -> UIViewController? {
        Smooch.newConversationListViewController()
    }
}
