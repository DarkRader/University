//
//  CountryListTest.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 03.02.2023.
//

import SwiftUI

struct CountryListTest: View {
  var body: some View {
    List(NSLocale.isoCountryCodes, id: \.self) { countryCode in
      HStack {
        Text(countryFlag(countryCode))
        Text(Locale.current.localizedString(forRegionCode: countryCode) ?? "")
        Spacer()
        Text(countryCode)
      }
    }
  }
    func countryFlag(_ countryCode: String) -> String {
      String(String.UnicodeScalarView(countryCode.unicodeScalars.compactMap {
        UnicodeScalar(127397 + $0.value)
      }))
    }
}

struct CountryListTest_Previews: PreviewProvider {
    static var previews: some View {
        CountryListTest()
    }
}
