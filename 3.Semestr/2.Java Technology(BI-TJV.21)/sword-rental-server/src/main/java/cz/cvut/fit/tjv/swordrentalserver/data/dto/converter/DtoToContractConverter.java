package cz.cvut.fit.tjv.swordrentalserver.data.dto.converter;

import cz.cvut.fit.tjv.swordrentalserver.business.PersonService;
import cz.cvut.fit.tjv.swordrentalserver.business.SwordService;
import cz.cvut.fit.tjv.swordrentalserver.data.dto.ContractDto;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Contract;
import org.modelmapper.ModelMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.function.Function;

@Component
public class DtoToContractConverter implements Function<ContractDto, Contract> {
    @Autowired
    private ModelMapper modelMapper;

    private final PersonService personService;

    private final SwordService swordService;

    public DtoToContractConverter(PersonService personService, SwordService swordService) {
        this.personService = personService;
        this.swordService = swordService;
    }

    @Override
    public Contract apply(ContractDto contractDto) {
        Contract newContract = modelMapper.map(contractDto, Contract.class);
        newContract.setPerson(personService.readById(contractDto.getPerson()).get());
        newContract.setSword(swordService.readById(contractDto.getSword()).get());
        return newContract;
    }
}
