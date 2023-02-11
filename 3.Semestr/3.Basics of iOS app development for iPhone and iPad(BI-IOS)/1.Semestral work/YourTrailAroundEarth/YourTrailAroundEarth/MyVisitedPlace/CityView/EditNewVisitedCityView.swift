//
//  EditNewVisitedCityView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 11.02.2023.
//

import SwiftUI

struct EditNewVisitedCityView: View {
    
    private var city: CoreDataCity
    
    init(city: CoreDataCity) {
        self.city = city
    }
    
    var body: some View {
        Text(/*@START_MENU_TOKEN@*/"Hello, World!"/*@END_MENU_TOKEN@*/)
    }
}

struct EditNewVisitedCityView_Previews: PreviewProvider {
    static var previews: some View {
        EditNewVisitedCityView(city: CoreDataCity())
    }
}
