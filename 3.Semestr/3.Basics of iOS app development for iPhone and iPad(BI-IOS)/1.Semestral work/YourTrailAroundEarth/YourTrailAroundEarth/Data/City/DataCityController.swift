//
//  DataCityController.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 06.02.2023.
//

import CoreData

final class DataCityController: ObservableObject {
    let container = NSPersistentContainer(name: "CityModel")
    
    init() {
        container.loadPersistentStores { description, error in
            if let error = error {
                print("Core data failed to load: \(error.localizedDescription)")
            }
        }
    }
}
