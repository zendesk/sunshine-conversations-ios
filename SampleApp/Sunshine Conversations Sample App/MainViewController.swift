//
// MainViewController.swift
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

final class MainViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
    }

    @IBAction func showConversationButtonTapped(_ sender: UIButton) {
        guard let conversationViewController = SunshineConversationsWrapper.shared.conversationViewController() else { return }
        navigationController?.pushViewController(conversationViewController, animated: true)
    }

    @IBAction func showConversationListButtonTapped(_ sender: UIButton) {
        guard let conversationListViewController = SunshineConversationsWrapper.shared.conversationListViewController() else { return }
        navigationController?.pushViewController(conversationListViewController, animated: true)
    }

}

