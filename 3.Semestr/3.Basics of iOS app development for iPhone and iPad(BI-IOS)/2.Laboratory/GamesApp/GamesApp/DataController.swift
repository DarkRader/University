//
//  DataController.swift
//  GamesApp
//
//  Created by DarkRader on 06.12.2022.
//

import CoreData

/// Controller responsible for loading persistent stores.
final class DataController: ObservableObject {
    let container = NSPersistentContainer(name: "GamesModel")
    
    init() {
        container.loadPersistentStores { description, error in
            if let error = error {
                print("Core data failed to load: \(error.localizedDescription)")
            }
        }
    }
}
