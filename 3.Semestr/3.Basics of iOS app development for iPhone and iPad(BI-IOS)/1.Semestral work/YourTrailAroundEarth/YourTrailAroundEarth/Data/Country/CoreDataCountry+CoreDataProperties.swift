//
//  CoreDataCountry+CoreDataProperties.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 09.02.2023.
//
//

import Foundation
import CoreData


extension CoreDataCountry {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<CoreDataCountry> {
        return NSFetchRequest<CoreDataCountry>(entityName: "CoreDataCountry")
    }
    
    @NSManaged public var continent: String?
    @NSManaged public var currency: String?
    @NSManaged public var currencySymbol: String?

    @NSManaged public var capital: String?
    @NSManaged public var countryCode: String?
    @NSManaged public var flag: String?
    @NSManaged public var id: String?
    @NSManaged public var language: String?
    @NSManaged public var name: String?
    @NSManaged public var rating: Int16
    @NSManaged public var review: String?
    @NSManaged public var city: NSSet?
    
    public var wrappedId: String {
           id ?? "Unknow id country"
       }
       
       public var wrappedName: String {
           name ?? "Unknow name country"
       }
       
       public var wrappedLanguage: String {
           language ?? "Unknow language country"
       }
       
       public var wrappedCountryCode: String {
           countryCode ?? "Unknow countryCode country"
       }
       
       public var wrappedCapital: String {
           capital ?? "Unknow capital country"
       }
       
       public var wrappedFlag: String {
           flag ?? "Unknow flag country"
       }
       
       public var wrappedRating: Int16 {
           rating
       }
       
       public var wrappedReview: String {
           review ?? "Unknow review country"
       }
       
       public var citiesList: [CoreDataCity] {
           let set = city as? Set<CoreDataCity> ?? []
           
           return set.sorted {
               $0.wrappedRating > $1.wrappedRating
           }
       }

}

// MARK: Generated accessors for city
extension CoreDataCountry {

    @objc(addCityObject:)
    @NSManaged public func addToCity(_ value: CoreDataCity)

    @objc(removeCityObject:)
    @NSManaged public func removeFromCity(_ value: CoreDataCity)

    @objc(addCity:)
    @NSManaged public func addToCity(_ values: NSSet)

    @objc(removeCity:)
    @NSManaged public func removeFromCity(_ values: NSSet)

}

extension CoreDataCountry : Identifiable {

}
