//
//  CountryWantToVisit.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 12.02.2023.
//

import Foundation

struct CountryWantToVisit: Identifiable, Codable {
    let id: String
    let countryCode: String
    let name: String
    let capital: String
    let flag: String
    let language: String
    
    let continent: String
    let currency: String
    let currencySymbol: String
}
