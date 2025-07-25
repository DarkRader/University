//
//  WantToVisiteView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 01.02.2023.
//

import SwiftUI

struct WantToVisiteView: View {
    
    var body: some View {
        NavigationStack {
            ScrollView {
                VStack {
                    VStack {
                        Text("Countries I want to visit")
                            .frame(maxWidth: .infinity, alignment: .leading)
                            .padding(.horizontal, 40)
                    
                        NavigationLink(destination: CountryWantToVisitView()) {
                            Image("Country")
                                .resizable()
                                .frame(width: 300, height: 200)
                                .clipShape(Rectangle())
                        }
                    }
                    .padding(.vertical, 30)
                    
                    VStack {
                        Text("Cities I want to visit")
                            .frame(maxWidth: .infinity, alignment: .leading)
                            .padding(.horizontal, 40)
                        
                        NavigationLink(destination: CityWantToVisitView()) {
                            Image("Сity")
                                .resizable()
                                .frame(width: 300, height: 200)
                                .clipShape(Rectangle())
                        }
                    }
                    
                    VStack {
                        Text("Places I want to visit")
                            .frame(maxWidth: .infinity, alignment: .leading)
                            .padding(.horizontal, 40)
                        
                        NavigationLink(destination: PlaceWantToVisitView()) {
                            Image("Place")
                                .resizable()
                                .frame(width: 300, height: 200)
                                .clipShape(Rectangle())
                        }
                    }
                    .padding(.vertical, 30)
                }
            }
        }
    }
}

struct WantToVisiteView_Previews: PreviewProvider {
    static var previews: some View {
        WantToVisiteView()
            .preferredColorScheme(.light)
        WantToVisiteView()
            .preferredColorScheme(.dark)
    }
}
