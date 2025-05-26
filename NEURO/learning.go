package main

import (
	"math"
	"math/rand"
	"time"
)

func ComputeMeanStd(data [][]float64) ([]float64, []float64) {
	nFeatures := len(data[0])
	means := make([]float64, nFeatures)
	stds := make([]float64, nFeatures)

	for j := 0; j < nFeatures; j++ {
		sum := 0.0
		for i := range data {
			sum += data[i][j]
		}
		means[j] = sum / float64(len(data))
	}

	for j := 0; j < nFeatures; j++ {
		sumSq := 0.0
		for i := range data {
			diff := data[i][j] - means[j]
			sumSq += diff * diff
		}
		stds[j] = math.Sqrt(sumSq / float64(len(data)))
		if stds[j] == 0 {
			stds[j] = 1
		}
	}
	return means, stds
} // расчет среднего и стандартного отклонения

func ApplyNormalization(data [][]float64, means, stds []float64) [][]float64 {
	normalized := make([][]float64, len(data))
	for i := range data {
		normalized[i] = make([]float64, len(data[i]))
		for j := range data[i] {
			normalized[i][j] = (data[i][j] - means[j]) / stds[j]
		}
	}
	return normalized
}

func GetY(data [][]float64) []float64 {
	var y []float64
	for i := range data {
		y = append(y, data[i][len(data[i])-1])
	}
	return y
}

func GetX(data [][]float64) [][]float64 {
	var x [][]float64
	for i := range data {
		var tmp []float64
		for j := 0; j < len(data[i])-1; j++ {
			tmp = append(tmp, data[i][j])
		}
		x = append(x, tmp)
	}
	return x
}

func SplitData(data [][]float64, trainRatio float64) (train [][]float64, test [][]float64) {
	rng := rand.New(rand.NewSource(time.Now().UnixNano()))
	indices := rng.Perm(len(data)) // случайная перестановка индексов

	splitPoint := int(trainRatio * float64(len(data)))
	// далее идет поэлементное прохождение по всему массиву с делением по splitPoint

	for i, idx := range indices {
		if i < splitPoint {
			train = append(train, data[idx])
		} else {
			test = append(test, data[idx])
		}
	}
	return
}

func Sigmoid(x float64) float64 {
	return 1.0 / (1.0 + math.Exp(-x))
}

func CalculateY(x []float64, weight []float64, b float64) float64 {
	y := 0.0
	for i := range x {
		y += x[i] * weight[i]
	}
	y += b
	return Sigmoid(y)
} // считает один Y

func GetLossFunction(def []float64, y []float64) float64 {
	var sum float64
	for i := range y {
		sum += def[i]*math.Log(y[i]) + (1-def[i])*math.Log(1-y[i])
	}
	return -sum / (float64(len(def)))
} // считает число для функции потерь

func GetGradientB(def []float64, y []float64) float64 {
	var sum float64
	for i := range y {
		sum += y[i] - def[i]
	}
	return sum / float64(len(y))
} // расчет градиента для B

func NewB(def []float64, y []float64, b float64, learningRate float64) float64 {
	gradB := GetGradientB(def, y)
	return b - learningRate*gradB
} // новый сдвиг

func GetGradientsW(x [][]float64, def []float64, y []float64) (gradients []float64) {
	for j := range x[0] {
		sum := 0.0
		for i := range y {
			sum += (y[i] - def[i]) * x[i][j]
		}
		gradients = append(gradients, sum/float64(len(y)))
	}
	return
} // получение массива градиентов для весов

func NewW(x [][]float64, def []float64, y []float64, w []float64, learningRate float64) (newW []float64) {
	gradW := GetGradientsW(x, def, y)
	for i := range w {
		newW = append(newW, w[i]-gradW[i]*learningRate)
	}
	return
} // новые веса

func GetAccuracy(def []float64, y []float64) float64 {
	correct := 0
	for i := range y {
		if (y[i] >= 0.5 && def[i] == 1.0) || (y[i] < 0.5 && def[i] == 0.0) {
			correct++
		}
	}
	return (float64(correct) / float64(len(def))) * 100.0
} // вычисление точности модели
