//
//  PushNotificationApp.swift
//  PushNotification
//
//  Created by DarkRader on 07.12.2022.
//

import SwiftUI

@main
struct PushNotificationApp: App {
    
    @UIApplicationDelegateAdaptor(AppDelegate.self) var appDelegate
    
    var body: some Scene {
        WindowGroup {
            ContentView()
        }
    }
}
