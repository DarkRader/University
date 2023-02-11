//
//  EditNewVisitedCountryView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 11.02.2023.
//

import SwiftUI

struct EditNewVisitedCountryView: View {
    
    private var country: CoreDataCountry
    
    init(country: CoreDataCountry) {
        self.country = country
    }
    
    var body: some View {
        Text(/*@START_MENU_TOKEN@*/"Hello, World!"/*@END_MENU_TOKEN@*/)
    }
}

struct EditNewVisitedCountryView_Previews: PreviewProvider {
    static var previews: some View {
        EditNewVisitedCountryView(country: CoreDataCountry())
    }
}
