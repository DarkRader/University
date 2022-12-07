//
//  PushManager.swift
//  PushNotification
//
//  Created by DarkRader on 07.12.2022.
//

import UserNotifications
import UIKit

final class PushManager {
    static let shared = PushManager()
    
    func start() {
        UNUserNotificationCenter.current().requestAuthorization(options: [.badge, .sound, .alert]) { granted, error in
            if granted {
                DispatchQueue.main.async
                UIApplication.shared.registerForRemoteNotifications()
            }
        }
    }
    
    func stop() {
        UIApplication.shared.unregisterForRemoteNotifications()
    }
}
