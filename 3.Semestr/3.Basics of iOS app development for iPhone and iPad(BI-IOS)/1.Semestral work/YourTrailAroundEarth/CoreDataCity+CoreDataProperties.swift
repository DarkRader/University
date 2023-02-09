//
//  CoreDataCity+CoreDataProperties.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 06.02.2023.
//
//

import Foundation
import CoreData


extension CoreDataCity {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<CoreDataCity> {
        return NSFetchRequest<CoreDataCity>(entityName: "CoreDataCity")
    }

    @NSManaged public var review: String?
    @NSManaged public var rating: Int16
    @NSManaged public var flag: String?
    @NSManaged public var name: String?
    @NSManaged public var id: String?
    @NSManaged public var origin: CoreDataCountry?
    
    public var wrappedId: String {
        id ?? "Unknow id City"
    }
    
    public var wrappedName: String {
        name ?? "Unknow name City"
    }
    
    public var wrappedRating: Int16 {
        rating
    }
    
    public var wrappedFlag: String {
        flag ?? "Unknow flag City"
    }
    
    public var wrappedReview: String {
        review ?? "Unknow review City"
    }
    
}

extension CoreDataCity : Identifiable {

}
