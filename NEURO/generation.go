package main

import (
	"math/rand"
	"strconv"
)

func BoolToFloat64(b bool) float64 {
	if b {
		return 1.0
	}
	return 0.0
}

type Client struct {
	Age            float64 // int
	MaritalStatus  float64 //string  // int // семейное положение
	Dependents     float64 // int
	Education      float64 // string  // int
	ResidenceYears float64 // int // как долго живёт по текущему адресу
	CreditRating   float64 // int
	LatePayments2Y float64 // int
	CurrentDebt    float64 // int
	ActiveLoans    float64 //int
	MaxOverdue1Y   float64 // int

	WasBankrupt           float64 // bool
	DebtVSIncome          float64
	MonthlyPayments       float64 // int
	MoneyPaidSubscription float64 // int
	Collateral            float64 // bool
	CreditVSCollateral    float64
	MonthlyIncome         float64 // int
	JobType               float64 // string  // int
	JobExperience         float64 // int
	AdditionalIncome      float64 // int

	BankRelationshipYears float64 // int
	AverageBalance        float64 // int
	CreditCardUsage       float64 // int
	CheckCreditHistory    float64 // int
	LoanPurpose           float64 //string  // int
	HasGuarantor          float64 // bool // поручитель
	Region                float64 //string  // int
	EarlyRepayments       float64 // bool
	HasCriminalRecord     float64 // bool
	NumberKids            float64 // int

	Default float64 // bool // int
}

func GenerateClient(rng *rand.Rand /*, marital, education, jobtypes, purposes, regions []string*/) Client {
	return Client{
		Age:            float64(rng.Intn(53) + 18),
		MaritalStatus:  float64(rng.Intn(4)), // marital[rng.Intn(len(marital))],
		Dependents:     float64(rng.Intn(4)),
		Education:      float64(rng.Intn(4)), // education[rng.Intn(len(education))],
		ResidenceYears: float64(rng.Intn(10) + 1),

		CreditRating:   float64(300 + rng.Intn(551)),
		LatePayments2Y: float64(rng.Intn(10)),
		CurrentDebt:    float64(int(rng.Float64() * 2_000_000)),
		ActiveLoans:    float64(rng.Intn(6)),
		MaxOverdue1Y:   float64(rng.Intn(91)),

		WasBankrupt:           BoolToFloat64(rng.Float32() < 0.1),
		DebtVSIncome:          rng.Float64() * 0.7,
		MonthlyPayments:       float64(int(rng.Float64() * 100_000)),
		MoneyPaidSubscription: float64(int(rng.Float64() * 2000)),
		Collateral:            BoolToFloat64(rng.Float32() < 0.3),

		CreditVSCollateral: rng.Float64() * 1.2,
		MonthlyIncome:      float64(int(rng.Float64() * 300_000)),
		JobType:            float64(rng.Intn(4)), // jobtypes[rng.Intn(len(jobtypes))],
		JobExperience:      float64(rng.Intn(11)),
		AdditionalIncome:   float64(int(rng.Float64() * 50_000)),

		BankRelationshipYears: float64(rng.Intn(16)),
		AverageBalance:        float64(int(rng.Float64() * 500_000)),
		CreditCardUsage:       float64(rng.Intn(21)),
		CheckCreditHistory:    float64(rng.Intn(6)),
		LoanPurpose:           float64(rng.Intn(3)), // purposes[rng.Intn(len(purposes))],

		HasGuarantor:      BoolToFloat64(rng.Float32() < 0.2),
		Region:            float64(rng.Intn(5)), // regions[rng.Intn(len(regions))],
		EarlyRepayments:   BoolToFloat64(rng.Float32() < 0.25),
		HasCriminalRecord: BoolToFloat64(rng.Float32() < 0.05),
		NumberKids:        float64(int(rng.Float64() * 10)),

		Default: 0.0, // false, // 0,
	}
}

func ClientToCSVRecord(c Client) []string {
	sum := int((c.Age)*(-0.3) + (c.MaritalStatus)*0.4 + (c.Dependents)*(-0.4) + (c.Education)*0.5 + (c.ResidenceYears)*0.2 +
		(c.CreditRating)*1.2 + (c.LatePayments2Y)*(-0.7) + (c.CurrentDebt)*(-1.0) + (c.ActiveLoans)*(-0.6) + (c.MaxOverdue1Y)*(-0.8) +
		(c.WasBankrupt)*(-1.1) + (c.DebtVSIncome)*(-0.4) + (c.MonthlyPayments)*(-0.6) + (c.MoneyPaidSubscription)*(-0.2) + (c.Collateral)*(-0.3) +
		(c.CreditVSCollateral)*(-1.0) + (c.MonthlyIncome)*1.2 + (c.JobType)*0.7 + (c.JobExperience)*0.4 + (c.AdditionalIncome)*0.8 +
		(c.BankRelationshipYears)*0.5 + (c.AverageBalance)*0.6 + (c.CreditCardUsage)*(-0.2) + (c.CheckCreditHistory)*(-0.5) + (c.LoanPurpose)*0.3 +
		(c.HasGuarantor)*0.2 + (c.Region)*0.4 + (c.EarlyRepayments)*1.0 + (c.HasCriminalRecord)*(-1.2) + (c.NumberKids)*(-0.3))
	var def float64
	if sum > 100_000 {
		def = 1.0
	} else {
		def = 0.0
	}

	return []string{
		strconv.FormatFloat(c.Age, 'f', 2, 64),
		strconv.FormatFloat(c.MaritalStatus, 'f', 2, 64), // c.MaritalStatus,
		strconv.FormatFloat(c.Dependents, 'f', 2, 64),
		strconv.FormatFloat(c.Education, 'f', 2, 64), // c.Education,
		strconv.FormatFloat(c.ResidenceYears, 'f', 2, 64),
		strconv.FormatFloat(c.CreditRating, 'f', 2, 64),
		strconv.FormatFloat(c.LatePayments2Y, 'f', 2, 64),
		strconv.FormatFloat(c.CurrentDebt, 'f', 2, 64),
		strconv.FormatFloat(c.ActiveLoans, 'f', 2, 64),
		strconv.FormatFloat(c.MaxOverdue1Y, 'f', 2, 64),

		strconv.FormatFloat(c.WasBankrupt, 'f', 2, 64),
		strconv.FormatFloat(c.DebtVSIncome, 'f', 2, 64),
		strconv.FormatFloat(c.MonthlyPayments, 'f', 2, 64),
		strconv.FormatFloat(c.MoneyPaidSubscription, 'f', 2, 64),
		strconv.FormatFloat(c.Collateral, 'f', 2, 64),
		strconv.FormatFloat(c.CreditVSCollateral, 'f', 2, 64),
		strconv.FormatFloat(c.MonthlyIncome, 'f', 2, 64),
		strconv.FormatFloat(c.JobType, 'f', 2, 64), // c.JobType,
		strconv.FormatFloat(c.JobExperience, 'f', 2, 64),
		strconv.FormatFloat(c.AdditionalIncome, 'f', 2, 64),

		strconv.FormatFloat(c.BankRelationshipYears, 'f', 2, 64),
		strconv.FormatFloat(c.AverageBalance, 'f', 2, 64),
		strconv.FormatFloat(c.CreditCardUsage, 'f', 2, 64),
		strconv.FormatFloat(c.CheckCreditHistory, 'f', 2, 64),
		strconv.FormatFloat(c.LoanPurpose, 'f', 2, 64), // c.LoanPurpose,
		strconv.FormatFloat(c.HasGuarantor, 'f', 2, 64),
		strconv.FormatFloat(c.Region, 'f', 2, 64), // c.Region,
		strconv.FormatFloat(c.EarlyRepayments, 'f', 2, 64),
		strconv.FormatFloat(c.HasCriminalRecord, 'f', 2, 64),
		strconv.FormatFloat(c.NumberKids, 'f', 2, 64),

		strconv.FormatFloat(def, 'f', 2, 64),
	}
}
