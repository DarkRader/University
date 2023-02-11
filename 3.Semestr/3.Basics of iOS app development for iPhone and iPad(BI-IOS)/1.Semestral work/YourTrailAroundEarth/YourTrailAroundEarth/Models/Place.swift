//
//  Place.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 09.02.2023.
//

import Foundation

struct Place: Identifiable, Codable {
    let id: String
    let name: String
    let rating: Int
    let review: String
    
    let street: String
    let number: String
    let postal_code: String
    let type: String
}
