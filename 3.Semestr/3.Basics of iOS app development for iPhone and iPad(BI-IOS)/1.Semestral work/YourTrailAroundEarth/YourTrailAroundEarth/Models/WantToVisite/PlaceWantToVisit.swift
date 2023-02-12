//
//  PlaceWantToVisit.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 12.02.2023.
//

import Foundation

struct PlaceWantToVisit: Identifiable, Codable {
    let id: String
    let name: String
    
    let country: String
    let flag: String
    let city: String
    
    let street: String
    let number: String
    let postal_code: String
    let type: String
}
