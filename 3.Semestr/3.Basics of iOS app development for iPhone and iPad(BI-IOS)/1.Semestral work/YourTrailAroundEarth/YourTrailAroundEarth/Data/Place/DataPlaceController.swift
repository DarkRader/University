//
//  DataPlaceController.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 09.02.2023.
//

import CoreData

final class DataPlaceController: ObservableObject {
    let container = NSPersistentContainer(name: "PlaceModel")
    
    init() {
        container.loadPersistentStores { description, error in
            if let error = error {
                print("Core data failed to load: \(error.localizedDescription)")
            }
        }
    }
}
