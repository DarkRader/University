//
//  City.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 06.02.2023.
//

import Foundation

struct City: Identifiable, Codable {
    let id: String
    let name: String
    let region: String
    let rating: Int
    let review: String
}
