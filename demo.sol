// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract HospitalBedRegistration {
    struct Bed {
        address patientAddress;
        bool isOccupied;
    }

    mapping(uint256 => Bed) public beds;
    uint256 public totalBeds;

    event BedRegistered(uint256 bedNumber, address patientAddress);

    constructor(uint256 _totalBeds) {
        totalBeds = _totalBeds;
        // Initialize the beds
        for (uint256 i = 1; i <= totalBeds; i++) {
            beds[i].isOccupied = false;
        }
    }

    function registerBed(uint256 bedNumber) external {
        require(bedNumber > 0 && bedNumber <= totalBeds, "Invalid bed number");
        require(!beds[bedNumber].isOccupied, "Bed is already occupied");

        beds[bedNumber].patientAddress = msg.sender;
        beds[bedNumber].isOccupied = true;

        emit BedRegistered(bedNumber, msg.sender);
    }
}
