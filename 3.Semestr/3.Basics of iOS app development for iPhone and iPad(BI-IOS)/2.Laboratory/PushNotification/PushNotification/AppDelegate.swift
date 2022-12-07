//
//  AppDelegate.swift
//  PushNotification
//
//  Created by DarkRader on 07.12.2022.
//

import Foundation

final class AppDelegate: UIResponder, UIApplicationDelegate {
    var window: UIWindow?
    
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOption: [UIApplication.LaunchOptionsKey : Any]? = nil) -> Bool {
        PushManager.shared.start()
        
        return true
    }
}
