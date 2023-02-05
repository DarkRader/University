//
//  CountryWantToVisitView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 03.02.2023.
//

import SwiftUI

struct CountryWantToVisitView: View {
    
    var body: some View {
        NavigationStack {
            VStack {
                Image("Country")
                    .resizable()
                    .frame(width: 500, height: 300)
                    .clipShape(Rectangle())
            }
            .navigationTitle("Сountry")
            .navigationBarTitleDisplayMode(.inline)
            .toolbar(.hidden, for: .tabBar)
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
//                    NavigationLink(destination: AddCountryWantToVisitView()) {
                    NavigationLink(destination: TestView()) {
                        Image(systemName: "plus")
                    }
                }
            }
        }
    }
}

struct CountryWantToVisitView_Previews: PreviewProvider {
    static var previews: some View {
        CountryWantToVisitView()
            .preferredColorScheme(.light)
        CountryWantToVisitView()
            .preferredColorScheme(.dark)
    }
}
