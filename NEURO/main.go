package main

import (
	"encoding/csv"
	"fmt"
	"log"
	"math/rand"
	"os"
	"time"

	"image/color"

	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
	"gonum.org/v1/plot/vg"
	"gonum.org/v1/plot/vg/draw"
)

func TransformClient(client Client) []float64 {
	return []float64{
		client.Age, client.MaritalStatus, client.Dependents, client.Education, client.ResidenceYears,
		client.CreditRating, client.LatePayments2Y, client.CurrentDebt, client.ActiveLoans, client.MaxOverdue1Y,
		client.WasBankrupt, client.DebtVSIncome, client.MonthlyPayments, client.MoneyPaidSubscription, client.Collateral,
		client.CreditVSCollateral, client.MonthlyIncome, client.JobType, client.JobExperience, client.AdditionalIncome,
		client.BankRelationshipYears, client.AverageBalance, client.CreditCardUsage, client.CheckCreditHistory, client.LoanPurpose,
		client.HasGuarantor, client.Region, client.EarlyRepayments, client.HasCriminalRecord, client.NumberKids, client.Default,
	}
}

func main() {

	////////////////////////////////////////////////////////////
	//////////////////// GENERATION OF DATA ////////////////////
	////////////////////////////////////////////////////////////

	rng := rand.New(rand.NewSource(time.Now().UnixNano()))

	file, err := os.Create("clients.csv")
	if err != nil {
		panic(err)
	}
	defer file.Close() // откладывает закрытие файла

	writer := csv.NewWriter(file)
	defer writer.Flush() // откладывает сброс буфера

	headers := []string{
		"Age", "MaritalStatus", "Dependents", "Education", "ResidenceYears",
		"CreditRating", "LatePayments2Y", "CurrentDebt", "ActiveLoans", "MaxOverdue1Y", "WasBankrupt",
		"DebtVSIncome", "MonthlyPayments", "MoneyPaidSubscription", "Collateral", "CreditVSCollateral",
		"MonthlyIncome", "JobType", "JobExperience", "AdditionalIncome",
		"BankRelationshipYears", "AverageBalance", "CreditCardUsage", "CheckCreditHistory",
		"LoanPurpose", "HasGuarantor", "Region", "EarlyRepayments", "HasCriminalRecord", "NumberKids", "Default",
	}
	writer.Write(headers)

	// maritalStatuses := []string{"Single", "Married", "Divorced", "Widowed"}
	// educationLevels := []string{"Secondary", "Specialized", "Higher", "PhD"}
	// jobTypes := []string{"Employed", "Self-Employed", "Business", "Unemployed"}
	// regions := []string{"Moscow", "St Petersburg", "Siberia", "Urals", "Far East"}
	// loanPurposes := []string{"Consumer", "Mortgage", "Refinancing"}

	buffer := make([][]string, 0, 1000)
	var matrix [][]float64

	for i := 0; i < 1000; i++ {
		c := GenerateClient(rng)
		// maritalStatuses,
		// educationLevels,
		// jobTypes,
		// loanPurposes,
		// regions)
		listC := TransformClient(c)
		matrix = append(matrix, listC)

		record := ClientToCSVRecord(c)
		buffer = append(buffer, record)

		if len(buffer) == 1000 {
			writer.WriteAll(buffer)
			buffer = buffer[:0] // очистка массива буфера
		}
	}

	///////////////////////////////////////////////////////////
	///////////////// PREPARING FOR LEARNING //////////////////
	///////////////////////////////////////////////////////////

	learningRate := 0.1
	train, test := SplitData(matrix, 0.8)

	defTrainY := GetY(train)
	defTestY := GetY(test)
	trainX := GetX(train)
	testX := GetX(test)

	means, stds := ComputeMeanStd(trainX)
	trainX = ApplyNormalization(trainX, means, stds)
	testX = ApplyNormalization(testX, means, stds)

	w := []float64{
		0.3, 0.8, -0.6, 1.0, 0.4,
		2.0, -0.1, -0.6, 0.1, -1.1,
		-1.0, 0.3, -0.8, 0.3, 0.1,
		-0.8, 1.0, 0.5, -0.3, 0.4,
		-0.1, 0.7, 0.4, -0.7, 0.4,
		-0.1, 0.5, 0.8, -1.0, -0.4,
	}
	b := 10.0
	epochs := 170
	threshold := 85.0
	fmt.Printf("Started weights: %v\n", w)
	fmt.Printf("Bias: %f\n", b)
	fmt.Printf("Number of epochs: %d\n", epochs)

	///////////////////////////////////////////////////////////
	///////////////////// LEARNING PROCESS ////////////////////
	///////////////////////////////////////////////////////////

	var list_epoch []float64
	var list_accuracy []float64

	for epoch := 0; epoch < epochs; epoch++ {
		var predY []float64
		for i := range trainX {
			y := CalculateY(trainX[i], w, b)
			predY = append(predY, y)
		}
		// LossFunction := GetLossFunction(def, predY)
		b = NewB(defTrainY, predY, b, learningRate)
		w = NewW(trainX, defTrainY, predY, w, learningRate)

		var testingY []float64
		for i := range testX {
			y := CalculateY(testX[i], w, b)
			testingY = append(testingY, y)
		}
		accuracy := GetAccuracy(defTestY, testingY)
		list_epoch = append(list_epoch, float64(epoch))
		list_accuracy = append(list_accuracy, accuracy)
	}

	var testingY []float64
	for i := range testX {
		y := CalculateY(testX[i], w, b)
		testingY = append(testingY, y)
	}
	accuracy := GetAccuracy(defTestY, testingY)
	if accuracy >= threshold {
		fmt.Printf("Final accuracy: %.2f%%\n", accuracy)
	}

	////////////////////////////////////////////////////////////
	///////////////////// VISUALIZATION ////////////////////////
	////////////////////////////////////////////////////////////

	pts := make(plotter.XYs, len(list_epoch))
	for i := range list_epoch {
		pts[i].X = list_epoch[i]
		pts[i].Y = list_accuracy[i]
	}

	p := plot.New()
	p.Title.Text = "Accuracy VS Epoch graph"
	p.X.Label.Text = "Epoch"
	p.Y.Label.Text = "Accuracy"

	scatter, err := plotter.NewScatter(pts)
	if err != nil {
		log.Fatal(err)
	}

	scatter.GlyphStyle.Radius = vg.Points(0.8)
	scatter.GlyphStyle.Color = color.RGBA{R: 0, G: 0, B: 0, A: 255}
	scatter.GlyphStyle.Shape = draw.CircleGlyph{}
	p.Add(scatter)

	if err := p.Save(6*vg.Inch, 4*vg.Inch, "graphS.png"); err != nil {
		log.Fatal(err)
	}
}
