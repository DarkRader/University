//
//  CoreDataPlace+CoreDataProperties.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 09.02.2023.
//
//

import Foundation
import CoreData


extension CoreDataPlace {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<CoreDataPlace> {
        return NSFetchRequest<CoreDataPlace>(entityName: "CoreDataPlace")
    }
    
    @NSManaged public var street: String
    @NSManaged public var number: String
    @NSManaged public var postal_code: String
    @NSManaged public var type: String

    @NSManaged public var review: String?
    @NSManaged public var rating: Int16
    @NSManaged public var name: String?
    @NSManaged public var id: String?
    @NSManaged public var origin: CoreDataCity?
    
    public var wrappedId: String {
           id ?? "Unknow id Place"
       }
       
    public var wrappedName: String {
       name ?? "Unknow name Place"
    }

    public var wrappedRating: Int16 {
       rating
    }

    public var wrappedReview: String {
       review ?? "Unknow review City"
    }

}

extension CoreDataPlace : Identifiable {

}
