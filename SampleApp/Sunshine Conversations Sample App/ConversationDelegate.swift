//
// ConversationDelegate.swift
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

final class ConversationDelegate: NSObject, SKTConversationDelegate {
    func conversation(_ conversation: SKTConversation, didShow viewController: UIViewController) {
        print("Showing conversation: \(String(describing: conversation.conversationId)).")
    }
}
