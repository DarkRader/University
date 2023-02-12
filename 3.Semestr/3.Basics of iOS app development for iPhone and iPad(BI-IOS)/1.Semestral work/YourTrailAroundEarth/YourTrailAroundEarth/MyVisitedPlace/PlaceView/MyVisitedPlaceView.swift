//
//  MyVisitedPlaceView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 09.02.2023.
//

import SwiftUI

struct MyVisitedPlaceView: View {
    @State private var mapAPI = MapAPI()
    
    @State private var showingAddScreen = false
    
    @State private var showMap = false
    
    @State private var selectedObject: CoreDataPlace?
    
    @State var showError = false
    
    @FetchRequest private var places: FetchedResults<CoreDataPlace>
    
    @Environment(\.managedObjectContext) private var moc
    
    private var keyName: String
    
    private var letter: String
    
    private var city: CoreDataCity
    
    init(keyName: String, letter: String, city: CoreDataCity) {
        self.keyName = keyName
        self.letter = letter
        self.city = city
        
        _places = FetchRequest<CoreDataPlace>(
            sortDescriptors: [
                SortDescriptor(\.rating, order: .reverse),
                SortDescriptor(\.name)
            ]

        )
    }
    
    var body: some View {
        NavigationStack {
            Text(city.name ?? "")
                .fontWeight(.heavy)
            List {
                ForEach(city.placiesList, id: \.self) { place in
                    VStack(alignment: .leading) {
                                                
                        placeView(for: place)                        
                        getPositionView(for: place, for: mapAPI)
                        showReviewView(for: place, for: selectedObject)

                        Text("Rating: \(String(place.rating))")
                        
                    }
                    .swipeActions {
                        Button(action: {
                            deleteCoreDataPlaces(place: place)
                       }) {
                           Text("Delete")
                               .background(Color.red)
                       }
                       .tint(Color.red)
                        
                        NavigationLink(destination: EditNewVisitedPlaceView(place: place)) {
                           Text("Edit")
                        }
                        .tint(Color.blue)
                    }
                }
            }
            .navigationTitle("Visited places")
            .toolbar(.hidden, for: .tabBar)
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button {
                        showingAddScreen.toggle()
                    } label: {
                        Label("Add a new place", systemImage: "plus")
                    }
                }
            }
        }
        .sheet(isPresented: $showMap) {
            ShowLocationOnMapView(mapAPI: $mapAPI)
        }
        .sheet(isPresented: $showingAddScreen) {
            AddNewVisitedPlaceView(showError: $showError, city: city)
        }
        .alert(isPresented: $showError) {
            Alert(title: Text("Error"), message: Text("This place is not located in this city, this place is not a place or this place not exist. Check the place that you wrote"), dismissButton: .default(Text("OK")))
        }
    }
    
    private func showReviewView(for place: CoreDataPlace, for selectedObject: CoreDataPlace?) -> some View {
        return VStack(alignment: .leading) {
            Button(action: {
                self.selectedObject = self.selectedObject == place ? nil : place
            }) {
                Text("Show review:")
            }
            .buttonStyle(BorderlessButtonStyle())
            
            if self.selectedObject == place {
                Text(place.review ?? "")
            }
        }
    }
    
    private func getPositionView(for place: CoreDataPlace, for mapAPI: MapAPI) -> some View {
       return HStack {
            Button(action: {
                mapAPI.getLocation(address: place.street, delta: 0.01)
            }) {
                Image(systemName: "location")
            }
            .buttonStyle(BorderlessButtonStyle())

            Button(action: {
                showMap.toggle()
            }) {
                Image(systemName: "mappin.and.ellipse")
            }
            .buttonStyle(BorderlessButtonStyle())
        }
    }
    
    private func placeView(for place: CoreDataPlace) -> some View {
        return VStack(alignment: .leading) {
            if place.type == "address" {
                Text("Street: \(place.street)")
                    .fontWeight(.medium)
                Text("Number of the street: \(place.number)")
                    .fontWeight(.medium)
                Text("Postal code: \(place.postal_code)")
                    .fontWeight(.medium)
            } else {
                Text("Venue: \(place.name ?? "")")
                    .fontWeight(.medium)
            }
        }
    }
    
    private static func loadPlacesFromFileSystem() -> [Place] {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(PlaceSave.url)

        guard let url = url else { return [] }

        do {
            let placesData = try Data(contentsOf: url)

            do {
                let places = try JSONDecoder().decode([Place].self, from: placesData)
                return places
            } catch {
                print("PLACES DECODING ERROR:", error.localizedDescription)
            }
        } catch {
            print("PLACES LOADING ERROR:", error.localizedDescription)
        }

        return []
    }

    private static func loadPlacesFromUserDefaults() -> [Place] {
        guard
            let placesData = UserDefaults.standard.data(forKey: PlaceSave.userDefaultsKey)
        else { return [] }

        do {
            let places = try JSONDecoder().decode([Place].self, from: placesData)
            return places
        } catch {
            print("PLACES DECODING ERROR:", error.localizedDescription)
        }

        return []
    }
    
    private func deleteCoreDataPlaces(place: CoreDataPlace) {
        moc.delete(place)

        try? moc.save()
    }
}

struct MyVisitedPlaceView_Previews: PreviewProvider {
    static var previews: some View {
        MyVisitedPlaceView(keyName: "title", letter: "S", city: CoreDataCity())
    }
}
