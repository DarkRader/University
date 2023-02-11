//
//  CoreDataCity+CoreDataProperties.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 09.02.2023.
//
//

import Foundation
import CoreData


extension CoreDataCity {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<CoreDataCity> {
        return NSFetchRequest<CoreDataCity>(entityName: "CoreDataCity")
    }

    @NSManaged public var region: String?
    @NSManaged public var id: String?
    @NSManaged public var name: String?
    @NSManaged public var rating: Int16
    @NSManaged public var review: String?
    @NSManaged public var origin: CoreDataCountry?
    @NSManaged public var place: NSSet?
    
    public var wrappedId: String {
           id ?? "Unknow id City"
       }
       
    public var wrappedName: String {
       name ?? "Unknow name City"
    }

    public var wrappedRating: Int16 {
       rating
    }

    public var wrappedRegion: String {
        region ?? "Unknow region City"
    }

    public var wrappedReview: String {
       review ?? "Unknow review City"
    }
    
    public var placiesList: [CoreDataPlace] {
        let set = place as? Set<CoreDataPlace> ?? []
        
        return set.sorted {
            $0.wrappedRating > $1.wrappedRating
        }
    }

}

// MARK: Generated accessors for place
extension CoreDataCity {

    @objc(addPlaceObject:)
    @NSManaged public func addToPlace(_ value: CoreDataPlace)

    @objc(removePlaceObject:)
    @NSManaged public func removeFromPlace(_ value: CoreDataPlace)

    @objc(addPlace:)
    @NSManaged public func addToPlace(_ values: NSSet)

    @objc(removePlace:)
    @NSManaged public func removeFromPlace(_ values: NSSet)

}

extension CoreDataCity : Identifiable {

}
