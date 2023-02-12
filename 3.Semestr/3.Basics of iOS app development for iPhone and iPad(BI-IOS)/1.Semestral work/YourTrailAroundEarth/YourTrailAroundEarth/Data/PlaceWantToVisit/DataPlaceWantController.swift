//
//  DataPlaceWantController.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 12.02.2023.
//

import CoreData

final class DataPlaceWantController: ObservableObject {
    let container = NSPersistentContainer(name: "PlaceWantModel")
    
    init() {
        container.loadPersistentStores { description, error in
            if let error = error {
                print("Core data failed to load: \(error.localizedDescription)")
            }
        }
    }
}
