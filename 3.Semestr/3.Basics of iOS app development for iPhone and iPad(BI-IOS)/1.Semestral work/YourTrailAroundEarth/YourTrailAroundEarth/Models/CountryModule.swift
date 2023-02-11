//
//  CountryModule.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 10.02.2023.
//

import Foundation

struct CountryModule: Codable {
    let data: [Datum]
}

struct Datum: Codable {
    let latitude, longitude: Double
    let type: String?
    let name: String?
    let country_code: String?
    let continent: String?
    let country_module: InfAboutCountry
}

struct InfAboutCountry: Codable {
    let capital: String?
    let currencies: [Currency]
    let languages: Lang
}

struct Currency: Codable {
    let symbol: String?
    let code: String?
    let name: String?
}

struct Lang: Codable {
    let code: String?
    let name: String?
}

