//
//  Country.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 04.02.2023.
//

import Foundation

struct Country: Identifiable, Codable {
    let id: String
    let name: String
    let capital: String
    let flag: String
    let language: String
    let rating: Int
    let review: String
    let photo: String
}
