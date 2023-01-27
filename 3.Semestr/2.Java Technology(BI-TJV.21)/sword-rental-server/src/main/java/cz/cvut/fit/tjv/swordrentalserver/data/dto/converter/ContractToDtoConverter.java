package cz.cvut.fit.tjv.swordrentalserver.data.dto.converter;

import cz.cvut.fit.tjv.swordrentalserver.data.dto.ContractDto;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Contract;
import org.modelmapper.ModelMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.function.Function;

@Component
public class ContractToDtoConverter implements Function<Contract, ContractDto> {
    @Autowired
    private ModelMapper modelMapper;

    @Override
    public ContractDto apply(Contract contract) {
        ContractDto newContractDto = modelMapper.map(contract, ContractDto.class);
        newContractDto.setPerson(contract.getPerson().getPersonId());
        newContractDto.setSword(contract.getSword().getSwordId());
        return newContractDto;
    }
}
